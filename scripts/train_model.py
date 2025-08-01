import pandas as pd
from sklearn.ensemble import RandomForestClassifier
import joblib

# Sample dataset (deadline_days, duration_hours, priority, free_time_hours, urgency)
data = pd.DataFrame([
    [1, 5, 5, 0.5, 1],  # Urgent
    [2, 4, 4, 1, 1],    # Urgent
    [7, 2, 3, 5, 0],    # Not urgent
    [10, 1, 1, 8, 0],   # Not urgent
    [3, 3, 5, 0.5, 1],  # Urgent
    [5, 2, 2, 4, 0]     # Not urgent
], columns=['deadline_days', 'duration_hours', 'priority', 'free_time_hours', 'urgency'])

X = data[['deadline_days', 'duration_hours', 'priority', 'free_time_hours']]
y = data['urgency']

model = RandomForestClassifier(n_estimators=100, random_state=42)
model.fit(X, y)

# Save the trained model
joblib.dump(model, '../models/urgency_model.pkl')
print("✅ Model trained and saved to ../models/urgency_model.pkl")
