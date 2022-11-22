export interface BirthCertificateDTO {
  id: number,
  text: string,
  location: string,
  date: string,
  healthGrade: number,
  petId: number
}

export interface BirthCertificatesDTO {
  birthCertificates: Array<BirthCertificateDTO>
}
