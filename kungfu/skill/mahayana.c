//mahayana.c  ������͹�
inherit SKILL;

string type() { return "knowledge"; }

int valid_learn(object me)
{
    if ((int)me->query("shen") < 0 )
       return notify_fail("���а��̫�أ��޷�����������͹���\n");

    return 1;
}

void skill_improved(object me)
{
}
