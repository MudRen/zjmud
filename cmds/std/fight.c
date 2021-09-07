// fight.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object obj, old_target;

	if (me->is_chatter())
		return 0;

	if (environment(me)->query("no_fight"))
		return notify_fail("�����ֹս����\n");
      
	if (!arg || !objectp(obj = present(arg, environment(me))))
		return notify_fail("���빥��˭��\n");
   
	if (! obj->is_character())
		return notify_fail("�����һ�㣬�ǲ��������\n");
	if (obj->query("owner") == me->query("id")) return notify_fail("�㾹Ȼ�۸��Լ��ĳ��̫���˵��˰ɣ�����\n");
	if (obj->is_fighting(me))
		return notify_fail("���ͣ����ͣ����ͣ�\n");

	if (! living(obj))
		return notify_fail(obj->name() + "�Ѿ��޷�ս���ˡ�\n"); 

	if (me->query("qi") < me->query("max_qi") * 3 / 10)
		return notify_fail("������û������ս���ˡ�\n");

	if (obj == me) return notify_fail("�㲻�ܹ����Լ���\n");
	
	if (obj->query("can_speak"))
	{
		message_vision("\n$N����$n˵����" 
			+ RANK_D->query_self(me)
			+ me->name() + "�����"
			+ RANK_D->query_respect(obj) + "�ĸ��У�\n\n", me, obj);

		if( objectp(old_target = me->query_temp("pending/fight")) )
			tell_object(old_target, YEL + me->name() + "ȡ���˺�����Ե���ͷ��"NOR"\n");
		me->set_temp("pending/fight", obj);

		notify_fail("������" + obj->name() + "��������������\n");
		switch (obj->accept_fight(me))
		{
		case 0:
			return userp(obj);
		case -1:
			return 1;
		default:
		}

		me->fight_ob(obj);
		obj->fight_ob(me);
	} else
	{
		message_vision("\n$N���һ������ʼ��$n����������\n\n", me, obj);
		me->fight_ob(obj);
		obj->kill_ob(me);
	}

	return 1;
}
int help(object me)
{
	write(@HELP
ָ���ʽ : fight <����>
 
���ָ��������һ������ֽ̡������ǡ��д����ա���������ʽ��ս��������
�㵽Ϊֹ�����ֻ����������������������ˣ����ǲ��������е�  NPC ��ϲ��
��ܣ���������״����ı���Ҫ��ᱻ�ܾ���
 
�������ָ��: kill

PS. ����Է���Ը����������ս������Ȼ���������� kill ָ�ʼս������
    �� fight �� kill �������뿴 'help combat'.
HELP );
	return 1;
}
