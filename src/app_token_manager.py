import requests
from config_loader import load_config


class AppTokenManager:
    def __init__(self, config_path=None):
        self.config = load_config(config_path)
        self.app_id = self.config['app_id']
        self.app_secret = self.config['app_secret']
        self.folder_token = self.config['folder_token']
        self._tenant_access_token = None
        self.docx_base_url = self.config.get('docx_base_url', 'https://xyv2stoud3.feishu.cn/docx')

    def get_tenant_access_token(self):
        if self._tenant_access_token:
            return self._tenant_access_token
        url = "https://open.feishu.cn/open-apis/auth/v3/tenant_access_token/internal"
        resp = requests.post(url, json={
            "app_id": self.app_id,
            "app_secret": self.app_secret
        })
        resp.raise_for_status()
        data = resp.json()
        self._tenant_access_token = data['tenant_access_token']
        return self._tenant_access_token
