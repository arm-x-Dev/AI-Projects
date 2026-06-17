#include "WiFi.h"

// --- MAX NETWORK TRACKING LIMIT ---
#define MAX_TRACKED_NETWORKS 30

// --- 1D KALMAN FILTER CLASS (YOUR EXACT LOGIC) ---
class KalmanFilter1D {
 private:
  float q; // Process variance
  float r; // Measurement variance 
  float x; // Filtered value
  float p; // Estimation error covariance
  float k; // Kalman gain
  
 public:
  KalmanFilter1D(float process_variance = 0.5, float measurement_variance = 2.0, float initial_value = -70.0) {
   q = process_variance;
   r = measurement_variance;
   x = initial_value;
   p = 1.0;
  }
  
  float update(float measurement) {
   p = p + q; // Prediction update
   k = p / (p + r); // Measurement update
   x = x + k * (measurement - x);
   p = (1 - k) * p;
   return x;
  }
  
  float getValue() { return x; }
};

// Structure to pair a specific MAC address to its dedicated Kalman filter instance
struct TrackedNetwork {
  String bssid;
  KalmanFilter1D* filter;
};

TrackedNetwork registry[MAX_TRACKED_NETWORKS];
int registryCount = 0;

// Look up an existing filter or instantiate a new one dynamically for a fresh MAC address
KalmanFilter1D* getOrCreateFilter(String bssid, int currentRawRssi) {
  for (int i = 0; i < registryCount; i++) {
    if (registry[i].bssid == bssid) {
      return registry[i].filter;
    }
  }
  
  // If registry is full, overwrite older network memory slot to save allocation space
  if (registryCount >= MAX_TRACKED_NETWORKS) {
    delete registry[0].filter;
    for (int i = 1; i < MAX_TRACKED_NETWORKS; i++) {
      registry[i-1] = registry[i];
    }
    registryCount--;
  }
  
  // Create fresh filter configuration for the newly discovered device
  int newIdx = registryCount;
  registry[newIdx].bssid = bssid;
  registry[newIdx].filter = new KalmanFilter1D(0.5, 2.0, (float)currentRawRssi);
  registryCount++;
  return registry[newIdx].filter;
}

void setup() {
  Serial.begin(115200);
  
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("{\"status\": \"Kalman Wi-Fi Filter Matrix Initialized\"}");
}

void loop() {
  // Scan for networks (false = asynchronous off, true = hide hidden networks)
  int n = WiFi.scanNetworks(false, true);
  
  if (n > 0) {
    String jsonOutput = "{\"networks\": [";
    
    for (int i = 0; i < n; ++i) {
      String bssid = WiFi.BSSIDstr(i);
      int rawRssi = WiFi.RSSI(i);
      
      // Pass raw signal data into the dedicated Kalman math engine instance
      KalmanFilter1D* targetFilter = getOrCreateFilter(bssid, rawRssi);
      float filteredRssi = targetFilter->update((float)rawRssi);
      
      jsonOutput += "{";
      jsonOutput += "\"ssid\":\"" + WiFi.SSID(i) + "\",";
      // Output the perfectly smoothed value back to the web console
      jsonOutput += "\"rssi\":" + String(filteredRssi, 1);
      jsonOutput += "}";
      
      if (i < n - 1) {
        jsonOutput += ",";
      }
    }
    
    jsonOutput += "]}";
    Serial.println(jsonOutput); // Ship stream down the USB pipeline cord
  }

  WiFi.scanDelete();
  delay(1500); // Scan sweep velocity pace
}