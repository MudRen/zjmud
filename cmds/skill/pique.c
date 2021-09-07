// pique.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
	int pts, max_pts;

	pts = 0;
	if (! arg || (arg != "none" && ! sscanf(arg, "%d", pts)))
		return notify_fail("ָ���ʽ��pique|jianu <ʹ�����ɷ�ŭ�˵�>|none\n");

	max_pts = me->query_max_craze() / 100;
	if (max_pts < 1)
		return notify_fail("����Ը񲻺ϣ��޷�ʹ�÷�ŭ������\n");

	if (pts > max_pts)
		return notify_fail("��ÿ�γ���ֻ��ʹ�� " + max_pts + " ���ŭ��\n");
	if (pts == 0)
		me->delete("jianu");
	else
		me->set("jianu", pts);

	write("Ok.\n");
	return 1;
}

int help (object me)
{
	write(@HELP
ָ���ʽ: pique|jianu <ʹ�������ŭ�˵�>|none
 
���ָ������ָ��ÿ�λ��е���ʱ��Ҫ���������ŭ���˺��Է�����
��ʹ���˷�ŭ�˵У����ڹ����л���һ���ļ��ʿ���ʹ����ŭ��ɱ��
��ŭ��ʽ��

pique none ���ʾ�㲻ʹ�÷�ŭ��

HELP );
	return 1;
}
