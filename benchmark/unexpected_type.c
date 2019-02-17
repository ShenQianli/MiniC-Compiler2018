int a;
int b;
int c[2];
int putint(int x);
int main(){
	a = 1;
	b = 2;
	c[0] = 1;
	c[a==1] = 2;
	a = a == 1;
	a = (a == 1) + b;
	if(a == (b == 2))
		return 1;
	if(b)
		return 0;
	return a == 1;
}
