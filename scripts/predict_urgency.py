import sys
import joblib
import numpy as np

# Arguments: deadline, duration, priority, free_time
if len(sys.argv) != 5:
    print("Usage: python3 predict_urgency.py <deadline> <duration> <priority> <free_time>")
    sys.exit(1)

deadline = float(sys.argv[1])
duration = float(sys.argv[2])
priority = float(sys.argv[3])
free_time = float(sys.argv[4])

# Load model
model = joblib.load('models/urgency_model.pkl')

# Predict
X = np.array([[deadline, duration, priority, free_time]])
pred = model.predict(X)
print(int(pred[0]))
