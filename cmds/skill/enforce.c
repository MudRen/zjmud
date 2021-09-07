// enforce.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int pts;

	if( !arg || (arg!="none" && arg!="max" && !sscanf(arg, "%d", pts)) ) 
		return notify_fail(INPUTTXT("��Ҫ�ö��������˵У�","enforce $txt#")+"\n"
					ZJOBACTS2+ZJMENUF(3,3,8,30)+"���:enforce max"ZJSEP"ȡ������:enforce none\n");

	if( !me->query_skill_mapped("force") )
		return notify_fail("������� enable һ���ڹ���\n");

	if( arg=="none" )
	{
		me->delete("jiali");
		write("Ok��������ȡ���˸��������˵С�\n");
	}
	else if( arg=="max" )
	{
		if( (pts=(int)me->query_skill("force")/2)<=0 )
			return notify_fail("���ڹ��ȼ�̫���ˡ�\n");
		me->set("jiali", pts);
		write("Ok��������ʹ��"+pts+"���ӵ������˵С�\n");
	}
	else {
		if( pts < 0 || pts > (int)me->query_skill("force") / 2 )
			return notify_fail("��ֻ���� none ��ʾ���������������ֱ�ʾÿһ���ü���������\n");
		me->set("jiali", pts);
		write("Ok��������ʹ��"+arg+"���ӵ������˵С�\n");
	}

	return 1;
}

int help (object me)
{
	write(@HELP
ָ���ʽ: enforce|jiali <ʹ�����������˵�>|none
 
���ָ������ָ��ÿ�λ��е���ʱ��Ҫ�������������˵С�

enforce none ���ʾ�㲻ʹ�������� 

See Also: enable
HELP );
	return 1;
}
