// save.c
inherit F_CLEAN_UP;
int main(object me, string arg)
{
	object link_ob;
	int lasttime;
	seteuid(getuid());

	if( !objectp(link_ob = me->query_temp("link_ob")) )
		return notify_fail("�㲻�Ǿ����������߽��룬���ܴ��档\n");

	lasttime = time() - (int)me->query("last_save");
	if( lasttime >= 0 && lasttime < 30)
		return notify_fail("Ϊ�˽���ϵͳ���أ��벻ҪƵ��������ȡ�\n");

	if( environment(me)->query("valid_startroom") ) {
		me->set("startroom", base_name(environment(me)));
		write("�����´����߽���ʱ��������￪ʼ��\n");
	}

	if( (int)link_ob->save() && (int)me->save() ) {
		write("����������ϡ�\n");
		me->set("last_save", time());
		return 1;
	} else {
		write("����ʧ�ܡ�\n");
		return 0;
	}
}

int help(object me)
{
	write(@HELP
ָ���ʽ��save

��������ܶ��Ľ����������
HELP
	);
	return 1;
}
