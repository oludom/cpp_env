FROM gcc:13.2.0

RUN apt-get update && apt-get install -y cmake gdb clang-format \
    && rm -rf /var/lib/apt/lists/*

# RUN apt-get update && apt-get install -y \
#   locales \
#   && locale-gen en_US.UTF-8 \
#   && update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8 \
#   && rm -rf /var/lib/apt/lists/*
# ENV LANG en_US.UTF-8

# # Install timezone
# RUN ln -fs /usr/share/zoneinfo/UTC /etc/localtime \
#   && export DEBIAN_FRONTEND=noninteractive \
#   && apt-get update \
#   && apt-get install -y tzdata \
#   && dpkg-reconfigure --frontend noninteractive tzdata \
#   && rm -rf /var/lib/apt/lists/*

ARG USERNAME=bent
ARG USER_UID=1000
ARG USER_GID=$USER_UID

# Create a non-root user
RUN groupadd --gid $USER_GID $USERNAME \
  && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USERNAME \
  # [Optional] Add sudo support for the non-root user
  && apt-get update \
  && apt-get install -y sudo \
  && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME\
  && chmod 0440 /etc/sudoers.d/$USERNAME \
  # Cleanup
  && rm -rf /var/lib/apt/lists/* \
  && echo "source /usr/share/bash-completion/completions/git" >> /home/$USERNAME/.bashrc
ENV DEBIAN_FRONTEND=