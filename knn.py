from pymongo.mongo_client import MongoClient
from pymongo.server_api import ServerApi
import numpy as np
from sklearn.neighbors import KNeighborsClassifier
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

uri = "mongodb+srv://duongquanbao19962012:Y019EMtRJwwzxZWG@cluster0.md6pcsr.mongodb.net/?retryWrites=true&w=majority&appName=Cluster0"
# Create a new client and connect to the server
client = MongoClient(uri, server_api=ServerApi('1'))
# Send a ping to confirm a successful connection
try:
    client.admin.command('ping')
    print("Pinged your deployment. You successfully connected to MongoDB!")
except Exception as e:
    print(e)


# Kết nối đến MongoDB
#client = MongoClient("mongodb://localhost:27017/")
db = client["demoLVTN"]
collection = db["order_detail"]

# Truy xuất dữ liệu từ MongoDB
data = []
labels = []
for record in collection.find():
    # Tạo một list để chứa giá trị pixels của hình ảnh
    image_data = []
    for i in range(1, 29):
        for j in range(1, 29):
            image_data.append(record[f"{i}x{j}"])
    
    # Thêm dữ liệu và nhãn vào danh sách tương ứng
    data.append(image_data)
    labels.append(record["label"])
# Chuyển đổi list thành numpy array
data = np.array(data)
labels = np.array(labels)

# Chuẩn bị dữ liệu cho KNN
# Reshape data về dạng 1D
n_samples = len(data)
data = data.reshape((n_samples, -1))

# Chia dữ liệu thành tập huấn luyện và tập kiểm tra
X_train, X_test, y_train, y_test = train_test_split(data, labels, test_size=0.2, random_state=42)

# Khởi tạo và huấn luyện mô hình KNN
knn = KNeighborsClassifier(n_neighbors=5)
knn.fit(X_train, y_train)

# Dự đoán trên tập kiểm tra
y_pred = knn.predict(X_test)

# Đánh giá độ chính xác
accuracy = accuracy_score(y_test, y_pred)
print("Accuracy:", accuracy)
