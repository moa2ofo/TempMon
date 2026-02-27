import os

def main():
    base_dir = os.path.dirname(os.path.abspath(__file__))

    for root, dirs, files in os.walk(base_dir):
        # Check if current directory is a 'src' folder
        if os.path.basename(root) == "src":
            for f in files:
                file_path = os.path.join(root, f)
                try:
                    os.remove(file_path)
                    print(f"Deleted: {file_path}")
                except Exception as e:
                    print(f"Error deleting {file_path}: {e}")

if __name__ == "__main__":
    main()