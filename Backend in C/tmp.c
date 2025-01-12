// POST

// DTO-DATA TRANSFER OBJECT

$dto (struct s_credentials, "cred")
struct s_credentials {
    char username[16];
    char password[16];
};

$post(login, "/users/login")
bool login(Request *req, Response *res){
    char *user,*pass;
    user = req->cred->username;
    pass = req->cred->password;

    if(!strcmp(user, "Rogan"
    && (!strcmp(pass, "red")))){
        req.session.loggedin = true;

        return json("{ 'loggedin': true}");

    }
    else{
        res.errorcode =  301;
        return httperror(res, "Unauthorized");

    }

}