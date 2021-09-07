// berserk.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int max;
	int pts;

	if ((max = me->query_max_craze()) < 1)
		return notify_fail("����Ը񲻺ϣ����Ʒ�����\n");

	if (me->query_con() < 35 && me->query_str() < 35)
		return notify_fail("����������ʻ������ã�óȻ�����������塣\n");

	if (me->is_busy())
		return notify_fail("������æ���ء�\n");

	if (me->query("neili") < 1000)
		return notify_fail("��������������棬���Կ����Լ���������\n");

	message_vision(HIR "$N" HIR "��Ȼ��Ц���ؽڿ��������������ͣ��һ�ɺ�����Ȼ����"NOR"\n", me);

	pts = max * random(me->query_skill("force") + 500) / 1000;
	me->improve_craze(pts);
	pts = pts * 10 / me->query_con();
	me->receive_damage("qi", pts);
	me->add("neili", -200 - random(200));
	me->start_busy(2);

	return 1;
}

int help (object me)
{
	write(@HELP
ָ���ʽ: berserk|baofa
 
���ָ�����������ڹ��������������з����������Լ��ķ�ŭ������
�������Լ�û�кô���ÿ�η����������Լ������ܵ���ʧ�������岻
֧��ʱ��ŭС�����ʡ�

HELP );
	return 1;
}
