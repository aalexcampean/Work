class Course {
    private _Id: number;
    public get Id(): number {
        return this._Id;
    }
    public set Id(value: number) {
        this._Id = value;
    }
    private _Name: String;
    public get Name(): String {
        return this._Name;
    }
    public set Name(value: String) {
        this._Name = value;
    }
    private _NoOfCredits: number;
    public get NoOfCredits(): number {
        return this._NoOfCredits;
    }
    public set NoOfCredits(value: number) {
        this._NoOfCredits = value;
    }
    private _IsOptional: boolean;
    public get IsOptional(): boolean {
        return this._IsOptional;
    }
    public set IsOptional(value: boolean) {
        this._IsOptional = value;
    }

    private _IsChecked: boolean;
    public get IsChecked(): boolean {
        return this._IsChecked;
    }
    public set IsChecked(value: boolean) {
        this._IsChecked = value;
    }

    private _IsDisabled: boolean;
    public get IsDisabled(): boolean {
        return this._IsDisabled;
    }
    public set IsDisabled(value: boolean) {
        this._IsDisabled = value;
    }
    
    constructor(Id : number, Name : String, NoOfCredits : number, IsOptional: boolean) {
        this._Id = Id;
        this._Name = Name;
        this._NoOfCredits = NoOfCredits;
        this._IsOptional = IsOptional;
        this._IsChecked = !IsOptional;
        this._IsDisabled = !IsOptional;
    }
}

export default Course;