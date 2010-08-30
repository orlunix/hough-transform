img=imread('readfile.bmp'); 
%img=imread('writefile.bmp');

img=rgb2gray(img); %comment by orlunix
edimg=edge(img); 
s=size(img); 
nr=s(1); 
nth=s(2); 
accarray=zeros(nr,nth); 
 
rmax=sqrt(s(1)^2+s(2)^2); 
dr=2*rmax/(nr-1); 
dth=pi/nth; 
th=[0:dth:(pi-dth)];  
 
for y=1:s(1), 
   for x=1:s(2) 
      if edimg(y,x)==1 
         r=(x*cos(th))+(y*sin(th)); 
         rdx=round(r/dr+nr/2); 
         for k=1:nth 
            accarray(rdx(k),k)=accarray(rdx(k),k)+1; 
         end 
      end 
   end 
end 
 array = accarray;
colormap gray; 
imagesc(accarray); 
 
m=max(accarray); 
mm=max(m); 
mn=min(m); 
th=round((mm+mn)/2); 
 
dr=2*rmax/(nr+1); 
%thimg=im2bw(accarray,th); 
thimg=im2bw(accarray,0.5); 
[l,num]=bwlabel(thimg); 
 
figure, imshow(img) 
 
for i=1:num 
   mask=l==i; 
   region=mask.*accarray; 
   [tmpc,tmpr]=max(region); 
   [tmax,col]=max(tmpc); 
   row=tmpr(col); 
    
   r=dr*(row-(nr/2)); 
   th=dth*(col-1); 
    
   line([0 s(2)], [(r/sin(th)) ((r-(s(2)*cos(th)))/sin(th))]); 
end
figure,imshow(img)