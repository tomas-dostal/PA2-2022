FROM amd64/debian:bullseye

RUN useradd -m -s /bin/bash progtest
RUN echo "root:root" | chpasswd
RUN echo "progtest:progtest" | chpasswd

ADD packages.sh /tmp
RUN bash -c "source /tmp/packages.sh && apt-get update && apt-get install -y \${PACKAGE_LIST_SPACES}"

RUN rm -rf /var/lib/apt/lists/* /tmp/packages.sh

USER progtest
WORKDIR /home/progtest/

CMD bash
