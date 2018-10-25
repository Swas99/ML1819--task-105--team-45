import struct
import numpy as np
from skimage.feature import hog
from sklearn.svm import LinearSVC
from sklearn.metrics import confusion_matrix

#loading images
def load(images):
    if images is "training":
        filedigit = 'train-images-idx3-ubyte/train-images.idx3-ubyte'
        filelabel = 'train-labels-idx1-ubyte/train-labels.idx1-ubyte'
    elif images is "testing":
        filedigit = 't10k-images-idx3-ubyte/t10k-images.idx3-ubyte'
        filelabel = 't10k-labels-idx1-ubyte/t10k-labels.idx1-ubyte'

    with open(filelabel, 'rb') as flbl:
        _, _ = struct.unpack(">II", flbl.read(8))
        label = np.fromfile(flbl, dtype=np.int8)

    with open(filedigit, 'rb') as fimg:
        _, _, rows, cols = struct.unpack(">IIII", fimg.read(16))
        digit = np.fromfile(fimg, dtype=np.uint8).reshape(len(label), rows, cols)

    getdigit = lambda idx: (label[idx], digit[idx])

    for i in range(len(label)):
        yield getdigit(i)

def computeScore(y,preds):
  # for training data X,y it calculates the number of correct predictions made by the model
  ##### replace the next line with your code #####
  score=sum(y==preds)
  return score

trainingdata=list(load(images="training"))
features = np.array([trainingdata[i][1] for i in range(60000)])
labels = np.array([trainingdata[i][0] for i in range(60000)])

#hog features
temphog = []
for feature in features:
    fd = hog(feature.reshape((28, 28)), orientations=9, pixels_per_cell=(14, 14), cells_per_block=(1, 1))
    temphog.append(fd)
hog_features = np.array(temphog, 'float64')

#Model fitting
LSVC = LinearSVC()
LSVC.fit(hog_features, labels)

#test picture preprocessing
trainingdata=list(load(images="testing"))
features = np.array([trainingdata[i][1] for i in range(10000)])
labels = np.array([trainingdata[i][0] for i in range(10000)])

#hog features
temphog = []
for feature in features:
    fd = hog(feature.reshape((28, 28)), orientations=9, pixels_per_cell=(14, 14), cells_per_block=(1, 1), visualise=False)
    temphog.append(fd)
hog_features = np.array(temphog, 'float64')
predictions = LSVC.predict(hog_features)

score = computeScore(predictions,labels)
print('accuracy = {0:.2f}%'.format(score/len(labels)*100))
print(confusion_matrix(predictions, labels))

##test picture preprocessing
#test = cv2.imread("2.jpg")
#gray = cv2.cvtColor(test, cv2.COLOR_BGR2GRAY)
#blur = cv2.GaussianBlur(gray, (5, 5), 0)
#_, thresholded = cv2.threshold(blur, 90, 255, cv2.THRESH_BINARY_INV)
#_, centers, _ = cv2.findContours(thresholded.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
#rectangles = [cv2.boundingRect(center) for center in centers]
#for rectangle in rectangles:
#    cv2.rectangle(test, (rectangle[0], rectangle[1]), (rectangle[0] + rectangle[2], rectangle[1] + rectangle[3]), (0, 0, 255), 3)
#    pt1 = int(rectangle[1] + rectangle[3] // 2 - int(rectangle[3]) // 2)
#    pt2 = int(rectangle[0] + rectangle[2] // 2 - int(rectangle[3]) // 2)
#    roi = thresholded[pt1:pt1+int(rectangle[3]), pt2:pt2+int(rectangle[3])]
#    roi = cv2.resize(roi, (28, 28), interpolation=cv2.INTER_AREA)
#    roi = cv2.dilate(roi, (3, 3))
#    roi_hog_fd = hog(roi, orientations=9, pixels_per_cell=(14, 14), cells_per_block=(1, 1), visualise=False)
#    #prediction of each digit
#    predictions = LSVC.predict(np.array([roi_hog_fd], 'float64'))
#    cv2.putText(test, str(int(predictions[0])), (int(rectangle[0] + rectangle[2]/2),int(rectangle[1] + rectangle[3]/2)),cv2.FONT_HERSHEY_PLAIN, 3, (0, 0, 255), 3)
#cv2.imshow("Digit Recognition", test)
#cv2.waitKey()
#cv2.destroyAllWindows()