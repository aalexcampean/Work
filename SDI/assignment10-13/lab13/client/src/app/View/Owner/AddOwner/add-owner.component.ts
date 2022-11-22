import {Component, Input, OnInit} from '@angular/core';
import {OwnerService} from "../../../Controller/owner-service";
import {OwnerDTO} from "../../../Model/ownerDTO";
import {OwnersModalComponent} from "../OwnersModal/owners-modal.component";
import {PetsModalComponent} from "../../ReusableComponents/PetsModal/pets-modal.component";
import {PetDTO} from "../../../Model/petDTO";
import {Router} from "@angular/router";

@Component({
  selector: 'add-owner',
  templateUrl: './add-owner.component.html',
  styleUrls: ['./add-owner.component.css', "../../ReusableComponents/ReusableStyling/TableStyling.css"]
})
export class AddOwnerComponent {
  inputId: string | null = null;
  inputFirstName: string | null = null;
  inputLastName: string | null = null;
  inputEmail: string | null = null;
  inputPhoneNumber: string | null = null;
  inputDateOfBirth: string | null = null;

  constructor(private ownerService: OwnerService, private router: Router) {
  }

  public addOwner() {
    let owner : OwnerDTO = {
      id: 0,
      firstName: this.inputFirstName!,
      lastName: this.inputLastName!,
      email: this.inputEmail!,
      phoneNumber: this.inputPhoneNumber!,
      dateOfBirth: this.inputDateOfBirth!
    }
    this.ownerService.addOwner(owner);
    this.router.navigate(['/owners'])
  }
}
