# from lark_oapi.api.docx.v1 import BatchUpdateDocumentBlockRequest, BatchUpdateDocumentRequestBody, 
import lark_oapi as lark
import json
from lark_oapi.api.docx.v1 import CreateDocumentRequest, CreateDocumentRequestBody
from lark_oapi.api.docx.v1 import UpdateDocumentRequest
from app_token_manager import AppTokenManager
import logging
from markdown_converter import markdown_to_feishu_blocks

logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


def create(client, token_manager) -> str:
    # 构造请求对象
    request = CreateDocumentRequest.builder() \
        .request_body(CreateDocumentRequestBody.builder()
                      .folder_token(token_manager.folder_token)
                      .title("第三坨")
                      .build()) \
        .build()

    # 发起请求
    response = client.docx.v1.document.create(request)

    # 处理失败返回
    if not response.success():
        lark.logger.error(
            f"client.docx.v1.document.create failed, code: {response.code}, msg: {response.msg}, log_id: {response.get_log_id()}, resp: \n{json.dumps(json.loads(response.raw.content), indent=4, ensure_ascii=False)}")
        return

    # 处理业务结果
    lark.logger.info(lark.JSON.marshal(response.data, indent=4))

    document_id = response.data.document.document_id
    docx_url = token_manager.docx_base_url + "/" + document_id
    return docx_url, document_id


# def update(client, document_id, blocks):
#     request = BatchUpdateDocumentBlockRequest.builder() \
#         .document_id(document_id) \
#         .request_body(BatchUpdateDocumentRequestBody.builder()
#                       .revision_id(-1)  # -1 表示最新版本
#                       .requests(blocks)  # blocks 是内容操作列表
#                       .build()) \
#         .build()
#     response = client.docx.v1.document.batch_update(request)
#     if not response.success():
#         # 错误处理
#         pass
#     return response


def main():
    token_manager = AppTokenManager()

    # 创建client
    client = lark.Client.builder() \
        .app_id(token_manager.app_id) \
        .app_secret(token_manager.app_secret) \
        .log_level(lark.LogLevel.DEBUG) \
        .build()

    # doc_url, document_id = create(client, token_manager)
    # logging.info(
    #     f"Created document URL: {doc_url}, Document ID: {document_id}")

    doc_url = "https://xyv2stoud3.feishu.cn/docx/HdbndgcLooB7GTx1OeOc4UvDnZe"
    document_id = "HdbndgcLooB7GTx1OeOc4UvDnZe"

    with open("test/doc.md", "r", encoding="utf-8") as f:
        md_content = f.read()

    logging.info(f"Markdown content:\n{md_content}")

    blocks = markdown_to_feishu_blocks(md_content)

    # update(client, document_id, blocks)


if __name__ == "__main__":
    main()
