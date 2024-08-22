import { Routes } from '@angular/router';
import { PublicComponent } from './pages/public/public.component';
import { LoginComponent } from './pages/login/login.component';
import { RegisterComponent } from './pages/register/register.component';
import { RecoverComponent } from './pages/recover/recover.component';
import { HomeComponent } from './pages/home/home.component';
import { CheeseComponent } from './pages/cheese/cheese.component';
import { NotFoundComponent } from './pages/not-found/not-found.component';
import { AuthGuard, redirectUnauthorizedTo } from '@angular/fire/auth-guard'

const redirectUnauthorizedToLogin = () => redirectUnauthorizedTo(['login']);
export const routes: Routes = [
    {path: '', component:PublicComponent},

    {path: 'login', component:LoginComponent},
    {path: 'register', component:RegisterComponent},
    {path: 'recover', component:RecoverComponent},
    
    {path: 'home', component:HomeComponent, canActivate:[AuthGuard], data:{authGuardPipe: redirectUnauthorizedToLogin}},
    {path: 'cheese', component:CheeseComponent, canActivate:[AuthGuard], data:{authGuardPipe: redirectUnauthorizedToLogin}},
    {path: 'cheese/:key', component:CheeseComponent, canActivate:[AuthGuard], data:{authGuardPipe: redirectUnauthorizedToLogin}},
    
    {path: '**', component:NotFoundComponent},
];