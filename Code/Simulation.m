delete(gcp('nocreate'));
cluster = parcluster('local');

% Ändern der Anzahl der Worker auf 15
cluster.NumWorkers = 14;

% Starten des parallelen Pools mit 15 Arbeitern
parpool(cluster, 14);

Stars = load('/home/niccollingro/Documents/ITG 1/ITG-Galaxiebewegung/Data/Startwerte.txt');
%Stars[0] = radius
%Stars[1] = degree
%Stars[2] = velocityRadius
%Stars[3] = velocityDegree
%Stars[4] = mass
%Arrays erzeugen
radius = Stars(: , 1);
degree = Stars(: , 2);
velocityRadius = Stars(: , 3);
velocityDegree = Stars(: , 4);
mass = Stars(: , 5);
radialForce = zeros(length(radius), 1);
angularForce = zeros(length(radius), 1);

%Variablen Deklarieren

massConstant = 1.989e30;
lightYearsInMeters = 9.461e15;
gravitationalConstant = 6.67430e-11;

conversionFactor = gravitationalConstant .* massConstant ./ sqrt(lightYearsInMeters.^2 - 2 .* lightYearsInMeters^2);

%Functions

superFastCalculator = @(i, j) mass(i) .* mass(j) .* conversionFactor ./ radius(i).^2 + radius(j).^2 - 2 .* radius(i) .* radius(j) .* cos(degree(i) - degree(j));


%Code
length(radius)

radius


parfor i = 1:length(radius)
    radialForceTemp = 0;
    angularForceTemp = 0;
    for j = 1:length(radius)
      if( i == j && j<length(radius)-1)
        Temp=0;
      else
        totalForce = mass(i) .* mass(j) .* conversionFactor ./ radius(i).^2 + radius(j).^2 - 2 .* radius(i) .* radius(j) .* cos(degree(i) - degree(j));
        radialForceTemp = radialForce(i) .* cos(degree(i) - degree(j));
        angularForceTemp = angularForce(i) .* sin(degree(i) - degree(j));
      end
    end
    radialForce(i) = radialForceTemp;
    angularForce(i) = angularForceTemp;
end
radialForce