inherit F_CLEAN_UP;

int main(object me, string arg)
{
	string f;
       if (! SECURITY_D->valid_grant(me, "(wizard)"))  
	      return 0;  
	if( !arg ) return notify_fail("ָ���ʽ��which <ָ��>\n");

	if( f = me->find_command(arg) ) {
		write(f + "\n");
		return 1;       
	}
	write("���ָ��·����û�����ָ������� localcmds ���ָ�\n");
	return 1;
}

     
