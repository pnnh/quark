import {getVisitorId} from "@/quark/atom/client/comments/fingerprint";
import {makeGet, makePost} from "@/quark/atom/client/http";
import {AccountModel} from "@/quark/atom/common/models/account";
import {PLGetResult, PLInsertResult} from "@/quark/atom/common/models/protocol";


export async function submitSignup(submitRequest: any) {
    submitRequest.fingerprint = await getVisitorId()
    // const url = getPortalPublicUrl() + '/account/signup'
    const url = '/account/signup'
    return await makePost(url, submitRequest) as PLInsertResult<AccountModel>
}

export async function accountSignin(submitRequest: any) {
    submitRequest.fingerprint = await getVisitorId()
    // const url = getPortalPublicUrl() + '/account/signin'
    const url = '/account/signin'
    return await makePost(url, submitRequest) as PLInsertResult<AccountModel>
}

export async function accountSignout(submitRequest: any) {
    submitRequest.fingerprint = await getVisitorId()
    // const url = getPortalPublicUrl() + '/account/signout'
    const url = '/account/signout'
    return await makePost(url, submitRequest)
}

export async function getUserinfo() {
    // const url = getPortalPublicUrl() + '/account/userinfo'
    const url = '/account/userinfo'
    return await makeGet(url) as PLGetResult<AccountModel>
}
