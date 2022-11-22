class Student{
    private _Id: number;
    public get Id(): number {
        return this._Id;
    }
    public set Id(value: number) {
        this._Id = value;
    }
    private _firstName: String;
    public get firstName(): String {
        return this._firstName;
    }
    public set firstName(value: String) {
        this._firstName = value;
    }
    private _lastName: String;
    public get lastName(): String {
        return this._lastName;
    }
    public set lastName(value: String) {
        this._lastName = value;
    }
    private _Group: number;
    public get Group(): number {
        return this._Group;
    }
    public set Group(value: number) {
        this._Group = value;
    }
    private _Year: number;
    public get Year(): number {
        return this._Year;
    }
    public set Year(value: number) {
        this._Year = value;
    }

    private _Grade: number;
    public get Grade(): number {
        return this._Grade;
    }
    public set Grade(value: number) {
        this._Grade = value;
    }
    
    constructor(Id : number, firstName : String, lastName : String, Group : number, Year:number, Grade:number) {
        this._Id = Id;
        this._firstName = firstName;
        this._lastName = lastName;
        this._Grade=Grade;
        this._Year = Year;
        this._Group = Group;
       
      
    }
}

export default Student;