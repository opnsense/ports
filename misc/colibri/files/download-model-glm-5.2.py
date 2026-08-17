import time
from huggingface_hub import snapshot_download

while True:
    try:
        print("Starting/Resuming download...")
        snapshot_download(
            repo_id="mateogrgic/GLM-5.2-colibri-int4-with-int8-mtp",
            local_dir=".",
            max_workers=4
        )
        print("Download complete!")
        break
    except Exception as e:
        print(f"Disconnected or Error: {e}. Retrying in 10 seconds...")
        time.sleep(10)

