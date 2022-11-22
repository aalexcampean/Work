export interface AppointmentDTO {
  id: number,
  petId: number,
  vetId: number,
  type: string,
  date: string,
}

export interface AppointmentsDTO {
  appointments: Array<AppointmentDTO>
}
