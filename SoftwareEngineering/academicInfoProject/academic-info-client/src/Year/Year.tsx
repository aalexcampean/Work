class Year {
    private _Id: number;
    public get Id(): number {
        return this._Id;
    }

    public set Id(value: number) {
        this._Id = value;
    }

    private _Year: number;
    public get Year(): number {
        return this._Year;
    }

    public set Year(value: number) {
        this._Year = value;
    }

    constructor(Id: number, Year: number) {
        this._Id = Id;
        this._Year = Year;
    }
}

export default Year;