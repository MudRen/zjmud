// taoism.c ��ѧ�ķ�
// modified by Venus Oct.1997

inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
    int lvl;

    lvl = (int)me->query_skill("taoism", 1);

    if(me->query("gender") == "����" && lvl > 19)
	return notify_fail("�����һ�������������Ժ���ԭ����û������֮\n"
			   "�����޷��������������仯֮����\n");

    return 1;
}

int practice_skill(object me)
{
    return notify_fail("��ʦ����ֻ�ܿ�ѧϰ����ߡ�\n");
}
