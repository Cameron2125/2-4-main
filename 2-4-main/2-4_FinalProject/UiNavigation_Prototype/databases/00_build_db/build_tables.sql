create table if not exists login (
      username   CHAR NOT NULL UNIQUE,
      password   CHAR NOT NULL,
      role       CHAR NOT NULL,
      email      CHAR NOT NULL
);

create table if not exists datapt_incentive (
      dataPt      CHAR NOT NULL UNIQUE,
      pointVal    INT NOT NULL
);

create table if not exists task_incentive (
      task  CHAR NOT NULL UNIQUE,
      pointVal    INT NOT NULL
);

.separator ","
.mode csv
.import "00_build_db/login.csv"  login
.import "00_build_db/datapt_incentive.csv" datapt_incentive
.import "00_build_db/task_incentive.csv" task_incentive