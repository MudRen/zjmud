// summon command.

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object ob;
	string str;
	int i;

	if (wiz_level(me) < 1 ||
	    ! SECURITY_D->valid_grant(me, "(immortal)"))
		return "/cmds/usr/summon"->main(me, arg);;

	if (! arg)
		return notify_fail("ָ���ʽ: Summon <player id> | <object>\n");

	if (sscanf(arg, ".%s", arg) ||
	    sscanf(arg, ". %s", arg))
		return "/cmds/usr/summon"->main(me, arg);

	str = arg;
	ob = find_player(str);
	if (! ob) ob = MESSAGE_D->find_user(str);
	if (objectp(ob) && ! me->visible(ob))
		ob = 0;
	if (! ob) ob = find_object(str);
	if (! ob)
	{
		str = resolve_path(me->query("cwd"), str);
		if (! sscanf(str, "%*s.c")) str += ".c";
		ob = find_object(str);
	}
	if (! ob)
		return "/cmds/usr/summon"->main(me, arg);

	if (wiz_level(ob) > wiz_level(me))
		return notify_fail("���߰���\n");

	if (environment(ob) == environment(me))
		return notify_fail("��... ����������ǰ��\n");

	if (environment(ob) == me)
		return notify_fail("��... ��������������\n");

	// moving
	tell_room(environment(ob), HIM "��������һֻ���ְ�"+
		  (string)ob->query("name") + HIM "ץ������, Ȼ�᲻���ˡ�"NOR"\n", ob);
	tell_object(ob,"һֻ�ְ���ץ������, ����ǰһ���....\n");
	tell_object(me, HIM "���" + ob->name() + HIM "ץ�������ǰ��"NOR"\n");
	tell_object(ob, HIM ".... ����ʱ������" + me->name() + HIM
		    "����Ū�����ġ�"NOR"\n");
	tell_room(environment(me), HIM + ob->name() + HIM "ͻȻ����" +
		  "������ǰ��"NOR"\n", ({ me, ob }));

	ob->move(environment(me));
      ob->set("startroom", "/d/city/kedian");

	// ok ..
	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : summon <ĳ��> | <��Ʒ> | .<��Ʒ>

��ָ�������(��)��ĳ�˻���Ʒץ������ǰ��

������ ID ����Ʒ������������ǰ���ע . ��ʾָ����Ʒ��

�������ڿ��Ա���Ȩʹ�õ���Ϣ������noneuser, user��all��
HELP );
	return 1;
}
