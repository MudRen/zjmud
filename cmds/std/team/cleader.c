// team command: emote

#include <ansi.h>

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object *t,ob;

	if (! pointerp(t = me->query_team()))
		return notify_fail("�����ڲ�û�кͱ�����ɶ��顣\n");
	if (! me->is_team_leader())
		return notify_fail("���ֲ��Ƕӳ����ƽ�ʲô��\n");
	if (!arg||!ob=find_player(arg)||!me->have_team_member(ob))
		return notify_fail("����Ѷӳ��ƽ���˭��\n");
	me->set_team_leader(ob);
	message("team", HIW "�����顿" + "��"+me->query("name")+"���ӳ��ƽ���"+ob->query("name")+NOR"\n", t);
	return 1;
}
