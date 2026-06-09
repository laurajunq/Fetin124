import { initializeApp } from 'firebase/app';

export const firebaseConfig = {
  apiKey: "AIzaSyBCNf-LCvB7PeVaamROQhKIZHgzuwuS-ME",
  authDomain: "handpulse.firebaseapp.com",
  projectId: "handpulse",
  storageBucket: "handpulse.firebasestorage.app",
  messagingSenderId: "508090679666",
  appId: "1:508090679666:web:5dfa1e7781860da2ca5deb",
  measurementId: "G-JHVWRGZGR9"
};

export const app = initializeApp(firebaseConfig);