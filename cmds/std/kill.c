// kill.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	object obj;
	string *killer, callname;

	if (me->is_chatter())
		return 0;

	if (! arg)
		return notify_fail("����ɱ˭��\n");

	if (! objectp(obj = present(arg, environment(me))))
		return notify_fail("����û������ˡ�\n");

	if (! obj->is_character() || obj->is_corpse())
		return notify_fail("�����һ�㣬�ǲ����ǻ��\n");
	 if (obj->query("owner") == me->query("id")) return notify_fail("�㾹ȻҪɱ�Լ��ĳ��̫���˵��˰ɣ�����\n");
	if (obj == me)
		return notify_fail("�� suicide ָ���ȽϿ�:)��\n");

	if (arrayp(me->query_team()) &&
	    member_array(obj, me->query_team()) != -1)
		return notify_fail("�����Լ������е���ҲҪɱ��̫���˵��˰ɣ�\n");

	if (me->is_fighting(obj) && me->is_killing(obj->query("id")))
		return notify_fail("�����ں��˼����������ء�\n");

	if ((me->query("age")<18 || me->query("combat_exp",1)<200000) && userp(obj) && !me->query_temp("in_pkd"))
		return notify_fail("СС��;���ɱ�˷Ż𣿻�������ȥ�ɡ�\n");

	if ((obj->query("age")<18 || obj->query("combat_exp",1)<200000) && userp(obj) && !obj->query_temp("in_pkd"))
		return notify_fail("��С���Ѷ�Ҫɱ���㻹�����ĺ�ѽ��\n");
	
	if (environment(me)->query("no_fight")&&!obj->query_condition("killer"))
		return notify_fail("���ﲻ׼ս����\n");
	
	if (! wizardp(me) && wizardp(obj))
		return notify_fail("��Ҳ�����ͼɱ������Ա��\n");

	if (! me->is_fighting(obj) &&
	    me->query("qi") < me->query("max_qi") * 3 / 10)
		return notify_fail("���Ѿ�û�ж�������ս���ˡ�\n");

	callname = RANK_D->query_rude(obj);

	if (obj->query("can_speak"))
	{
	    if (random(3) > 1)
	    message_vision("\n$N����$n�ȵ�����" 
		    + callname + "�����ղ������������һ��\n\n", me, obj);
	    else
	    message_vision("\n$N����$n�ȵ�����" 
		    + callname + "��������վ�����ļ��գ���\n\n", me, obj);
	}

	switch(obj->accept_kill(me))
	{
	case 0:
		return (! objectp(obj));
	case -1:
		return 1;
	default:
	}

	if (userp(me) && userp(obj) && ! obj->is_want_kill(me->query("id")) )
		// Recoder the player want to kill another player
		me->want_kill(obj);

	me->kill_ob(obj);
	if (living(obj) && ! userp(obj))
		obj->kill_ob(me);
	else
		obj->fight_ob(me);

	return 1;
}

int help(object me)
{
	write(@HELP
ָ���ʽ : kill <����>
 
���ָ������������ʼ����һ�����������ͼɱ���Է���kill �� fight ����
��ͬ���˫�������浶ʵǹ�ش򶷣�Ҳ����˵����������ˡ���� kill ֻ�赥��
��һ����Ը�Ϳ��Գ������������κ���ʹ�� kill ָ��Ὺʼս����ͨ�����
�Է��� NPC �Ļ�������Ҳ��ͬ������ʹ�� kill��

�����˶���ʹ�� kill ָ��ʱ����ֺ�ɫ�����������㣬���һ����Ҷ��ԣ����
��û�ж�һ������ʹ�ù� kill ָ��Ͳ��Ὣ�Է���Ĵ��˻�ɱ��( ʹ�÷�����
��)��

�������ָ��: hit, fight

�й� fight �� kill �������뿴 'help combat'.
HELP );
	return 1;
}
