export interface PetDTO {
  id: number,
  species: string,
  breed: string,
  name: string,
  dateOfEnrolment: string,
  ownerId: number
}

export interface PetsDTO {
  pets: Array<PetDTO>
}
