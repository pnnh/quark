import sha256 from 'crypto-js/sha256';
import md5 from 'crypto-js/md5';

export function encodeSHA256(data: string) {
    return sha256(data).toString();
}

export function encodeMD5(data: string) {
    return md5(data).toString();
}

export function encodeMD5Format(data: string) {
    const value = md5(data).toString();
    // 32位小写，UUID格式
    return `${value.substr(0, 8)}-${value.substr(8, 4)}-${value.substr(12, 4)}-${value.substr(16, 4)}-${value.substr(20, 12)}`;
}
