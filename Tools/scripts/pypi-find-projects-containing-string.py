#!/usr/bin/env python3
#
# MAINTAINER: yuri@FreeBSD.org

import argparse
import gzip
import json
import urllib.request


def filter_pypi_projects(search_term: str):
    """Downloads all PyPI project names, handles compression, filters, and prints them sorted."""
    url = "https://pypi.org/simple/"

    # Request JSON format and explicitly allow gzip compression while providing a standard User-Agent
    headers = {
        "Accept": "application/vnd.pypi.simple.v1+json",
        "Accept-Encoding": "gzip",
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) PyPiProjectFilter/1.0",
    }
    request = urllib.request.Request(url, headers=headers)

    try:
        with urllib.request.urlopen(request) as response:
            # Check if the content is gzipped and decompress safely
            if response.info().get("Content-Encoding") == "gzip":
                raw_data = gzip.decompress(response.read())
            else:
                raw_data = response.read()

            data = json.loads(raw_data.decode("utf-8"))

        project_names = [project["name"] for project in data.get("projects", [])]

        # Case-insensitive partial matching
        filtered_projects = [
            name for name in project_names if search_term.lower() in name.lower()
        ]

        filtered_projects.sort()

        for project in filtered_projects:
            print(project)

    except Exception as e:
        print(f"Error fetching or processing PyPI data: {e}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Download, filter, and sort PyPI projects safely."
    )
    parser.add_argument(
        "search_term",
        type=str,
        help="The string used to filter the PyPI project names (case-insensitive).",
    )

    args = parser.parse_args()
    filter_pypi_projects(args.search_term)
