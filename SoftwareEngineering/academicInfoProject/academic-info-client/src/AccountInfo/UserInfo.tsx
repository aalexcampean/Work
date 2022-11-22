class UserInfo {
    private _FirstName: string;
    public get FirstName(): string {
        return this._FirstName;
    }
    public set FirstName(value: string) {
        this._FirstName = value;
    }

    private _LastName: string;
    public get LastName(): string {
        return this._LastName;
    }
    public set LastName(value: string) {
        this._LastName = value;
    }

    private _EmailAddress: string;
    public get EmailAddress(): string {
        return this._EmailAddress;
    }
    public set EmailAddress(value: string) {
        this._EmailAddress = value;
    }

    private _PhoneNumber: string;
    public get PhoneNumber(): string {
        return this._PhoneNumber;
    }
    public set PhoneNumber(value: string) {
        this._PhoneNumber = value;
    }

    constructor(FirstName : string, LastName : string, EmailAddress : string, PhoneNumber: string) {
        this._FirstName = FirstName;
        this._LastName = LastName;
        this._EmailAddress = EmailAddress;
        this._PhoneNumber = PhoneNumber;
    }
}

export default UserInfo;