// whistle.c

#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string file;

	if (! arg)
		return notify_fail("��Ҫ�ٻ�ʲô��\n");
			
	if (me->is_busy() || me->query("doing"))  
		return notify_fail("��������æ�أ������п�����˵�ɡ�\n");
 
	if (me->is_in_prison())   
		return notify_fail("�����������أ������ʲô����\n"); 
			       
	if (me->is_ghost())
		return notify_fail("���㻹�������ٻ��ɡ�\n");

	if (! stringp(file = me->query("can_whistle/" + arg)))
		return notify_fail("�㲻֪������ٻ����ħ���ޡ�\n");

	if (file_size(file + ".c") < 0)
		return notify_fail("�㲻֪������ٻ����ħ���ޡ�\n");
	
	/*
	if (me->query("beastdied"))
		return notify_fail("���ħ�����Ѿ�����������<recall reborn>�����ȸ��\n");
	*/	
	if (environment(me)->query("no_magic") || environment(me)->query("no_fly")) 
		return notify_fail("�㷢�������е�Ź֣����ħ���޺����ܽ�����\n");    
	 
	call_other(file, "???");
	ob = find_object(file);

	if (! ob || ! ob->receive_whistle(me))
	{
		message_vision(HIM "$N" HIM "����һ�����ڡ�\n"
			       "Ȼ��ʲôҲû�з��� :)\n", me);
 }
	if (! ob) return 1;
	ob->reset_action();
	ob->set_leader(me);
	
	if (me->is_fighting())								     
		me->start_busy(1 + random(3));

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : whistle <ħ����ID>

��ָ�����������ħ���޺�����������Ȼ�����һ���ľ���ʩչ���С�
HELP );
	return 1;
}



