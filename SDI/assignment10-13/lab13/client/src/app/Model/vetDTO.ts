export interface VetDTO {
  id: number,
  firstName: string,
  lastName: string,
  email: string,
  phoneNumber: string,
  dateOfBirth: string,
  salary: number,
  rating: number
}

export interface VetsDTO {
  vets: Array<VetDTO>,
  total: number
}
