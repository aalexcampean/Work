import {Component, Input, OnInit} from '@angular/core';
import {OwnerService} from "../../../Controller/owner-service";
import {OwnerDTO} from "../../../Model/ownerDTO";
import {OwnersModalComponent} from "../OwnersModal/owners-modal.component";
import {PetsModalComponent} from "../../ReusableComponents/PetsModal/pets-modal.component";
import {PetDTO} from "../../../Model/petDTO";
import {Router, NavigationExtras} from "@angular/router";

@Component({
  selector: 'delete-owner',
  templateUrl: './delete-owner.component.html',
  styleUrls: ['./delete-owner.component.css', "../../ReusableComponents/ReusableStyling/TableStyling.css"]
})
export class DeleteOwnerComponent {
  inputFirstName: string | null = null;
  owners: Array<OwnerDTO> = [];


  constructor(private ownerService: OwnerService, private router: Router) {
    this.ownerService.getAllOwners()
      .subscribe(owner => this.owners = owner.owners);
  }

  public deleteOwnerByFirstName() {
    const deleteOwner = this.owners.find(owner => owner.firstName === this.inputFirstName);
    if (deleteOwner != null) {
      this.ownerService.deleteOwner(deleteOwner!.id);
      this.inputFirstName = "";
    } else {
      alert("No owner with this first Name")
    }
    this.router.navigate(['/owners'])
  }
}
