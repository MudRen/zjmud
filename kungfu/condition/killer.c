// killer.c

//#include <ansi.h>

int dispel() { return 0; }

int update_condition(object me, int duration)
{
	if (duration < 1)
	{
		tell_object(me, "�ٸ�����ͨ�����ˣ�\n");
		CHANNEL_D->do_channel(this_object(), "rumor",
			"��Ϊ" + me->name(1) + "һֱû�ܱ�" +
			"���ù鰸����˵�ٸ��Ѿ�ȡ����ͨ���");
		return 0;
	}
	me->apply_condition("killer", duration - 1);
	return 1;
}
