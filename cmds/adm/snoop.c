// snoop.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;

	if (! SECURITY_D->valid_grant(me, "(admin)"))
		return 0;

	if( !arg ) {
		if( objectp(ob = query_snooping(me)) )
			write("���������ڼ���" + ob->query("name") + "���յ���ѶϢ��\n");
		return 1;
	}
	if( objectp(ob = query_snooping(me))
	&&	wiz_level(ob) >= wiz_level(me) )
		tell_object(ob,
			HIW + me->name(1) + "ֹͣ���������յ���ѶϢ��"NOR"\n");
	if( arg=="none" ) {
		snoop(me);
		write("����ֹͣ��Ok��\n");
		return 1;
	}

	ob = find_player(arg);
	if(!ob) ob = find_living(arg);
	if(!ob || !me->visible(ob)) 
		return notify_fail("û������ˡ�\n");

	if( me==ob ) return notify_fail("���� snoop none ���������\n");
		
	if (!snoop(me, ob)) 
		return notify_fail("����ʧ�ܡ�\n");
		
	write("�����ڿ�ʼ����" + ob->name(1) + "���յ���ѶϢ��\n");
	
	if (wiz_level(ob) >= wiz_level(me))
		tell_object(ob, HIW + me->name(1) + "��ʼ���������յ���ѶϢ��"NOR"\n");
	if (geteuid(me) != "yuj" && userp(ob) && (wiz_level(ob)>3||!wiz_level(ob)))
		log_file("static/SNOOP_PLAYER", sprintf("%s(%s) snoops %s(%s) at %s on %s.\n",
			me->name(1), geteuid(me), ob->name(1), geteuid(ob), query_ip_name(ob), ctime(time()) ) );

	return 1;
}

int help()
{
	write(@TEXT
ָ���ʽ��snoop <ĳ��>|none

��������ʹ������������ѶϢ��snoop none ��ȡ��������
TEXT
	);
	return 1;
}
