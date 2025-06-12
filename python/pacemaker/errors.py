"""Pacemaker specific errors."""

__copyright__ = "Copyright 2025 the Pacemaker project contributors"
__license__ = "GNU Lesser General Public License version 2.1 or later (LGPLv2.1+)"
__all__ = ['PacemakerError']


class PacemakerError(Exception):
    """Base class for exceptions in the pacemaker package."""
