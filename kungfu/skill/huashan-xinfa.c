// huashan-xinfa.c ��ɽ�ķ�

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
    return (force == "zixia-shengong");
}

int valid_learn(object me)
{
    return ::valid_learn(me);
}

int practice_skill(object me)
{
    return notify_fail("��ɽ�ķ�ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
    return SKILL_D(__DIR__"huashan-xinfa/") + func;
}
