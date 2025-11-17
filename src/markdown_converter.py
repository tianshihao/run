import mistune


def markdown_to_feishu_blocks(md_text):
    markdown = mistune.Markdown()
    html = markdown(md_text)  # mistune 0.x/1.x 直接返回 HTML 字符串
    from bs4 import BeautifulSoup
    soup = BeautifulSoup(html, "html.parser")
    blocks = []
    for tag in soup.find_all(["h1", "h2", "h3", "h4", "h5", "h6", "p"]):
        if tag.name.startswith("h"):
            blocks.append({
                "type": "heading",
                "level": int(tag.name[1]),
                "content": [{"type": "text", "text": tag.get_text()}]
            })
        elif tag.name == "p":
            blocks.append({
                "type": "paragraph",
                "content": [{"type": "text", "text": tag.get_text()}]
            })
    return blocks


# 用法
md = "# 标题\n\n这是正文。"
blocks = markdown_to_feishu_blocks(md)
