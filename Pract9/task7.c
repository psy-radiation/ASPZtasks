#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Testing getent passwd:\n");
    
    // Нормальный вызов
    printf("\nNormal output:\n");
    system("getent passwd | head -n 3");
    
    // Симуляция проблем
    printf("\nSimulating problems:\n");
    
    // 1. Нет доступа к источникам данных
    printf("1. No access to databases:\n");
    system("getent -s nss_files,nss_db passwd 2>&1 | head -n 3");
    
    // 2. Поврежденные базы данных
    printf("\n2. Corrupted databases:\n");
    system("getent -s nss_files passwd nobody 2>&1");
    
    // 3. Сервис NSS не отвечает
    printf("\n3. NSS service not responding:\n");
    system("getent -s nss_ldap passwd 2>&1 | head -n 3");
    
    // 4. Проблемы с сетью для сетевых источников
    printf("\n4. Network issues:\n");
    system("getent -s nss_ldap passwd 2>&1 | grep -i 'no connection'");
    
    printf("\nPossible reasons for incomplete/invalid data:\n");
    printf("- No access to NSS databases\n");
    printf("- Corrupted password databases\n");
    printf("- Network issues for network-based NSS (LDAP, NIS)\n");
    printf("- Misconfigured NSS switches in /etc/nsswitch.conf\n");
    printf("- Permission denied for some sources\n");
    
    return 0;
}