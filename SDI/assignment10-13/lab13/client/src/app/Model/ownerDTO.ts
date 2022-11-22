export interface OwnerDTO {
  id: number,
  firstName: string,
  lastName: string,
  email: string,
  phoneNumber: string,
  dateOfBirth: string
}

export interface OwnersDTO {
  owners: Array<OwnerDTO>,
  total: number
}
