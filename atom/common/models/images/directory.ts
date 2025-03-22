export interface NPDirectoryModel {
    urn: string
    album: string
    album_name: string
    children: NPDirectoryModel[]
    level: number
    parent: string
    path: string
    profile: string
    profile_name: string
    title: string
    create_time: string
    update_time: string
    name: string
    description: string
    owner: string
}
