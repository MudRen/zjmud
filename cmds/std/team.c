// team.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object *t,ob;
	string str,add,*text,team_cmd;
	int i;

	if (! arg)
	{
		if (! pointerp(t = me->query_team()))
			return notify_fail(ZJOBLONG+HIG"�����ڲ�û�вμ��κζ��顣"NOR"\n");

		str = ZJOBLONG"�����ڶ����еĳ�Ա�У�\n"ZJOBACTS2+ZJMENUF(3,3,9,30);
		text = ({});
		for(i=0;i<sizeof(t);i++)
		{
			text += ({ t[i]->query("name")+":look "+file_name(t[i]) });
			if (me->is_team_leader())
			{
				if(i==0)
				{
					text += ({ "��ɢ����:team dismiss" });
					text += ({ "��������:team form" });
				}
				else
				{
					text += ({ "�߳�����:team dismiss "+file_name(t[i]) });
					text += ({ "�ӳ��ƽ�:team cleader "+file_name(t[i]) });
				}
			}
		}
		if(!me->is_team_leader())
			text += ({ "�뿪����:team dismiss" });
		str += implode(text,ZJSEP);
		write(str+"\n");
		return 1;
	}

	if (sscanf(arg, "%s %s", team_cmd, arg) != 2)
	{
		team_cmd = arg;
		arg = 0;
	}

	team_cmd = __DIR__"team/" + team_cmd + ".c";
	if (file_size(team_cmd) < 0)
		return notify_fail("��Ҫ��ʲô�������\n");

	return team_cmd->main(me, arg);
}

int help(object me)
{
	write( @HELP
����ָ��ʹ�÷���:

team with <ĳ��> - ��ĳ����ɶ���. ����Ҫ˫����ͬ�����Ż���Ч��
team dismiss     - �뿪����. ���´�ָ��������, ������������ɢ��
team talk <ѶϢ> - ����������������̸��, ������ tt <ѶϢ> �����
team form <��> - �����������ѧ���󷨵Ļ������Խ������еĳ�Ա��֯��
		   ĳ�����Σ�������ε�״ֻ̬Ҫ����һ�ƶ��ͻ�����

team kill <ĳ��> - ֻ�жӳ����ܹ������������������г�Աͬʱ���ĳ�ˡ�
		   ��ʹ�õ���������ʱ��������������Ԥ����������
		   ������ͼɱ���������е�ĳһ����Ա�Ļ�����ӳ��������
		   �����Ժ����еĳ�Ա��Ȼ��ͼɱ���Է������ǲ��ᱻ��Ϊ
		   ������PK�������������ĵĳͷ�����ʱ�����������Ķ���
		   �ڱ���ս���У���û��ͣ�ֹ������ζ����е������ˣ���ԭ
		   ��������������ң�Ҳ������������PK��Ҳ����˵����ͼɱ
		   ������ĳһ���˶��⵽�Է���ȫ�巴�˵�ʱ��ɱ���Է���
		   ��PK��¼Ҳֻ����һ����
		   ��һ�����������ӳ���������������Է������������
		   �еĳ�Ա������Ϊ�����������˹�������ô�Է����۴���˭
		   ������Ϊ��PK�����Է�����������ȫ���ɵ���Ҳ�������ܳ�
		   ������Ȼ���κ������ֻҪɱ�˹ٸ�����׷����

team swear <����>- ȫ�ӽ��塣ֻ�жӳ����ܹ�ʹ����������������е���
		   ������ϣ����Ϊ�ֵ�ͬ�ˣ��������ȫ����Ա���塣ͬʱ
		   ����Żｫ�ḳ��ӳ�ָ�������֡�ע�⣺һ�����ֻ�ܼ�
		   ��һ��������ͬ�ˣ������Ⲣ��Ӱ�����������ҽ���˽��
		   ֮��Ľ�ݡ�

ֱ���� team ָ��ʱ�����ʾ��Ŀǰ�Ƿ��м�����鼰��Ա������

ע: team �� follow �Ƕ����ģ��㲻һ��Ҫ follow ���������Ϳ��Ը���ӳ�
һ���ж���
HELP );
	return 1;
}

