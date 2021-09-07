// regiser: prison.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", HIR "��ʮ�˲����" NOR);
	set("long", @LONG
���Ｋ����ɭ����е������Ĺ�굽���ε������������Ҳ����͸
һ�ڣ�ֻ��Ͽ��뿪���Ҳ��֪������������ã��뵽����㲻
���е�����İ��ա�
    �Ա���һ�����ӡ�
LONG );
	set("no_fight", 1);
	set("item_desc", ([
		"�����ӡ�" : "��ʮ�˲���������뷭���Ǿ����ԣ�\n"
	]));
}

void init()
{
	add_action("do_suicide", "suicide");
}

int do_suicide()
{
	write("����ڤ����Ҳ����ɱ��ʡʡ�ɣ�\n");
	return 1;
}

void catch_back(object me)
{
	message_vision(HIM "��Ȼһ����ص��������������ܣ������������"
	       "��С�����˳�����һ��ץס$N" HIM "����\n������ס�����"
	       "�ݵĽе������üһ��������...��"NOR"\n",
	       me);

	message("vision", HIY "����һ����⣬���ʱʲôҲ��������...\n\n"
		  HIM "��������ɢȥ... " + me->name() +
		  "�����ˣ�����"NOR"\n",
		  environment(me), ({ me }));
}

void catch_ob(object me)
{
	message_vision(HIM "��Ȼһ����ص��������������ܣ������������"
		       "��С�����˳�����һ��ץס$N" HIM "����\n������ס�����"
		       "�ݵĽе�����վס���㷸���ˣ���������߰ɣ���"NOR"\n",
		       me);

	message("vision", HIY "����һ����⣬���ʱʲôҲ��������...\n\n"
			  HIM "��������ɢȥ... " + me->name() +
			  "�����ˣ�����"NOR"\n",
			  environment(me), ({ me }));
}

int free_ob(object me)
{
	string startroom;

	message_vision("��Ȼ����С��ð�˳�������ס$N���������ˣ������"
		       "���ˣ�Ҫ���ٸҷ������ߺ�...\n\n", me);
	message("vision", "����С���" + me->name() + "ͻȻ������ǰ��"
			  "ʧ��... �㲻��̾��һ������\n",
			  environment(me), ({ me }));

	tell_object(me, HIR "����ǰһ��..."NOR"\n");

	if (me->is_ghost())
		startroom = "/d/death/gate";
	else
		startroom = "/d/city/wumiao";

	me->set("startroom", startroom);
	me->move(startroom);
	message("vision", "һ����ص��������ֻ��" + me->name() +
			  "ֱͦͦ�����ڵ��ϡ�\n", environment(me), ({ me }));
	return 1;
}

