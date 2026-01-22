import tensorflow_datasets as tfds
import numpy as np


def ds_to_numpy(ds):
    images = []
    labels = []
    for image, label in ds:
        images.append(image.numpy())
        labels.append(label.numpy())
    return np.array(images).astype(np.float32)/255.00, np.array(labels).astype(np.float32)

def export_ds_to_files():
    train_ds, test_ds = tfds.load("mnist", split = ["train", "test"], as_supervised = True)

    train_images, train_labels = ds_to_numpy(train_ds)
    test_images, test_labels = ds_to_numpy(test_ds)

    print("Train Images: ", train_images.shape)
    print("Train Labels", train_labels.shape)

    print("Test Images: ", test_images.shape)
    print("Test Lables: ", test_labels.shape)

    train_images.tofile('./output/train_images.mat')
    test_images.tofile('./output/test_images.mat')
    return

def main():
    print("Starting to Porcess...")
    export_ds_to_files()
    print("done!")


if __name__ == "__main__":
    main()
