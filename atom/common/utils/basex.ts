import {base64url} from 'rfc4648'
import {parse as uuidParse, v4 as uuidv4} from 'uuid';
import {base58xrp,} from '@scure/base';
import md5 from "md5";

/**
 * 将字符串转换为base64编码的字符串
 * @param state - 待编码的字符串
 * @returns base64编码的字符串
 */
export function encodeBase64String(state: string): string {
    const enc = new TextEncoder()
    return base64url.stringify(enc.encode(state))
}

/**
 * 将base64编码的字符串转换为字符串
 * @param base64State - 待解码的base64编码的字符串
 * @returns 解码后的字符串
 */
export function decodeBase64String(base64State: string): string {
    const stateData = base64url.parse(base64State)
    const decoder = new TextDecoder()
    return decoder.decode(stateData)
}

export function binaryToBase58String(data: Uint8Array): string {
    return base58xrp.encode(data)
}

export function generateUuid(): string {
    return uuidv4();
}

export function stringToUuid(uuidString: string) {
    return uuidParse(uuidString).toString();
}

export function uuidToBase58(uuidString: string) {
    const data = uuidParse(uuidString);
    // 需要和服务器上的实现保持一致
    return base58xrp.encode(data);
}


function byteArrayToUUID(byteArray: Uint8Array) {
    if (byteArray.length !== 16) {
        throw new Error("Byte array must be exactly 16 bytes long to form a UUID.");
    }

    // Convert each byte to a two-digit hexadecimal string
    let hex = Array.from(byteArray, byte => byte.toString(16).padStart(2, '0')).join('');

    // Insert hyphens at the correct positions to form a UUID string
    return [
        hex.slice(0, 8),
        hex.slice(8, 12),
        hex.slice(12, 16),
        hex.slice(16, 20),
        hex.slice(20)
    ].join('-');
}

export function base58ToUuid(base58String: string) {
    const data = base58xrp.decode(base58String);
    let uuidString = byteArrayToUUID(data);
    return uuidString;
}

/**
 * 将字符串转换为base58编码的字符串
 * @param data - 待编码的字符串
 * @returns base58编码的字符串
 */
export function stringToBase58(data: string): string {
    const enc = new TextEncoder()
    return base58xrp.encode(enc.encode(data))
}

/**
 * 将base58编码的字符串转换为字符串
 * @param data - 待解码的base58编码的字符串
 * @returns 解码后的字符串
 */
export function base58ToString(data: string): string {
    const dec = new TextDecoder()
    return dec.decode(base58xrp.decode(data))
}

/**
 * 将字符串转换为md5字符串
 * @param data - 待转换的字符串
 * @returns md5字符串
 */
export function stringToMd5(data: string): string {
    const hash = md5(data)
    // 在md5字符串中间插入连字符
    return hash.slice(0, 8) + '-' + hash.slice(8, 12) + '-' + hash.slice(12, 16) + '-' + hash.slice(16, 20) + '-' + hash.slice(20)
}
