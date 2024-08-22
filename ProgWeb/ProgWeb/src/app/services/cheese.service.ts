import { Injectable } from '@angular/core';
import { addDoc, collection, collectionData, deleteDoc, doc, Firestore, docData, updateDoc } from '@angular/fire/firestore';
import { CheeseModel } from '../models/cheese.model';


@Injectable({
  providedIn: 'root'
})
export class CheeseService {
  private collectionRef;
  private loadingState=false;


  constructor(private db: Firestore) { 
    this.collectionRef = collection(db, 'cheeses');
}

  getCheese(key: string) {
    const cheeseRef = doc(this.collectionRef, key);
    return docData(cheeseRef);
  }

  getAllCheese(){
    return collectionData(this.collectionRef, {idField:'key'});
  }

  eatCheese(key: string){
    const cheeseRef = doc(this.collectionRef, key);
    return deleteDoc(cheeseRef);
  }

  async createCheese(cheese: CheeseModel){
    this.loadingState = true
    addDoc(this.collectionRef, cheese).finally(() => {this.loadingState = false})
  }
  
  async updateCheese(cheese: CheeseModel, key: string){
    this.loadingState = true
    const cheeseRef = doc(this.collectionRef, key);
    updateDoc(cheeseRef, {...cheese}).finally(() => {this.loadingState = false})
  }

  async saveCheese(cheese: CheeseModel, key: string | null = null){
    if (key){
      this.updateCheese(cheese, key)
    }
    else{
      this.createCheese(cheese)
    }
  }
  public get getLoading() {
    return this.loadingState;
  }
}
