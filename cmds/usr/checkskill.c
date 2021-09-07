// skill.c
#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

string *valid_types = ({
	"force",
	"dodge",
	"unarmed",
	"cuff",
	"strike",
	"finger",
	"hand",
	"claw",
	"sword",
	"blade",
	"staff",
	"hammer",
	"club",
	"whip",
	"dagger",
	"throwing",
	"parry",
	"magic",
	"medical",
	"poison",
	"chuixiao-jifa",
	"tanqin-jifa",
	"guzheng-jifa",
	"cooking",
});

// ��ѯ���ܵ�����

// ����������д˼��ܵĺ��������뷵��һ���� 0 �Ľ��
// �Ż����������Ӧ����������Ľ����

// $N ��ʾ�����ѯ����� $C ��ʾ�����ѯ��������ģ�
// $S ��ʾ�Ű��Ĳ�ѯ�����
mapping skill_features = ([
	"type"	      : "$C����", 
	"double_attack"     : "���ٹ���", 
	"main_skill"	: "������Ϊ$C", 
	"query_description" : "$S", 
]);

// ������Ϊ�˰�˳����ʾ
string *features = ({ "type", "double_attack", "main_skill", "query_description",  });

// ��ͷ�����ݣ�Ϊ�˱��ֶ�����趨
#define PREFIX_STR      "\t      "
// ÿ�еĳ���
#define LINE_LEN	40
// ��ʾ�ϲ�ʹ�õ��ַ�
#define COMBINE_STR     "��"
// ��ʾ����ʹ�õ��ַ�
#define APPOSE_STR      " - "
// ˮƽ��
#define HORIZONTAL_STR  HIC "����������������������������"\
			"������������������������������"NOR"\n"

string sort_result(string str, int prefix);

int main(object me, string arg)
{
	string  file, dir, filename;
	string  msg, msg1;
	string  type;
	int     i, l, is_force, prefix;
	int     perform, exert;
	mixed  *all_file;
	string *sub_skills, sub_skill;
	string feature, temp, *feature_list;
	mixed  *value;
	mapping sub_skill_list;

	seteuid(getuid());

	if (! arg)
		return notify_fail("ָ���ʽ��checkskill <��������> | <����������>\n");

	if (! stringp(file = SKILL_D(arg)) || file_size(file + ".c") <= 0)
	{
		// Ӣ�ĵ��Ҳ������Ǿ���������
		if (! stringp(arg = CHINESE_D->query_original(arg)))
			return notify_fail("û�����ּ��ܴ��ڡ�\n");

		write("Original: " + arg + "\n");
		// �����������ҵ���Ӣ�����������Ƿ�����д˼���
		if (! stringp(file = SKILL_D(arg)) || file_size(file + ".c") <= 0)
			return notify_fail("û�����ּ��ܴ��ڡ�\n");
	}

	msg = WHT + to_chinese(arg) + "(" + arg + ")����ϸ�������£�"NOR"\n";
	msg += HORIZONTAL_STR;
	msg += CYN + "  �������ƣ�  " WHT + to_chinese(arg) + "(" + arg + ")\n" + NOR;

	is_force = 0;

	if (SKILL_D(arg)->valid_enable("force"))
		is_force = 1;

	// ��ȡ���������б�
	feature_list = ({ });
	foreach (feature in features)
	{
		if (value = call_other(SKILL_D(arg), feature))
		{
			temp = skill_features[feature];

			if (stringp(value))
			{
				temp = replace_string(temp, "$N", value);
				temp = replace_string(temp, "$C", to_chinese(value));

				if (strsrch(temp, "$S") != -1)
				{
					prefix = strlen(implode(feature_list, COMBINE_STR)) + 
						 strlen(COMBINE_STR);
					temp = replace_string(temp, "$S", 
							      sort_result((string)value, prefix));
				}
			}
			feature_list += ({ temp });
		}
	}

	if (sizeof(feature_list))
		msg += CYN "\n  �������ԣ�  " WHT + implode(feature_list, COMBINE_STR) +
		       ""NOR"\n";

	if (member_array(arg, valid_types) != -1)
	{
		msg += CYN "\n  ����������  " WHT "��������"NOR"\n";
		msg += HORIZONTAL_STR;
		write(msg);
		return 1;
	}

	if (! wizardp(me) && me->query_skill(arg) <= 0)
	{
		msg += HORIZONTAL_STR;
		write(msg);
		return 1;
	}

	sub_skill_list = SKILL_D(arg)->query_sub_skills();
	if (mapp(sub_skill_list) && sizeof(sub_skill_list))
	{
		sub_skills = keys(sub_skill_list);
		msg += CYN "\n  ���ܺϳɣ�  " WHT;
		foreach (sub_skill in sub_skills)
		{
			if (file_size(SKILL_D(sub_skill) + ".c") <= 0)
				continue;

			msg += to_chinese(sub_skill) + "(" +
			       sub_skill + ")\n" + PREFIX_STR;
		}
		msg += NOR;
	}

	// ��ѯ���ܵ� pfm ���
	msg1 = "";
	perform = 0;
	dir = file;

	if (dir[strlen(dir) - 1] != '/')
		dir += "/";

	if (is_force)
		dir += "perform/";

	if (file_size(dir) != -2)
		msg1 += "";
	else
	{
		all_file = get_dir(dir);
		if (! sizeof(all_file))
			msg1 += "";
		else
		{
			for (i = 0; i < sizeof(all_file); i++)
			{
				filename = all_file[i];
				l = strlen(filename);
				if (filename[l - 1] == 'c' && filename[l - 2] == '.')
				{
					perform++;
					msg1 += (i == 0 ? "" : WHT + APPOSE_STR);
					msg1 += sprintf(WHT "%s" NOR, filename[0..l - 3]);
				}
			}

			if (msg1 != "")
			{
				msg += CYN "\n  ���ܾ��У�  " NOR;
				msg += msg1;
				msg += "\n";
			}
		}
	}

	// ��ѯ�ڹ��� exert ���
	if (! is_force)
	{
		msg += HORIZONTAL_STR;
		if (perform) msg += WHT "����" + chinese_number(perform) + "����С�"NOR"\n";
		write(msg);
		return 1;
	}

	msg1 = "";
	exert = 0;
	dir = file;

	if (dir[strlen(dir) - 1] != '/')
		dir += "/";
 
	if (file_size(dir + "exert/") == -2)
		all_file = get_dir(dir + "exert/");
	else
	if (file_size(dir) == -2)
		all_file = get_dir(dir);
	else
	{
		msg += HORIZONTAL_STR;
		write(msg);
		return 1;
	}

	if (! sizeof(all_file))
	{
		write(msg);
		return 1;
	}

	for (i = 0; i < sizeof(all_file); i++)
	{
		filename = all_file[i];
		l = strlen(filename);
		if (filename[l - 1] == 'c' && filename[l - 2] == '.')
		{
			exert++;
			msg1 += (i == 0 ? "" : WHT + APPOSE_STR);
			msg1 += sprintf(WHT "%s" NOR, filename[0..l - 3]);
		}
	}

	if (msg1 != "")
	{
		msg += CYN "  �ڹ����ܣ�  " NOR;
		msg += msg1;
		msg += "\n";
	}

	msg += HORIZONTAL_STR;

	if (perform)
	{
		msg += WHT "����" + chinese_number(perform) + "��ܾ���";
		if (exert)
			msg += "��" + chinese_number(exert) + "���ڹ����ܡ�"NOR"\n";
		else msg += "��"NOR"\n";
	} else
	if (exert)
		msg += WHT "����" + chinese_number(exert) + "���ڹ����ܡ�"NOR"\n";

	write(msg);
	return 1;
}

string sort_result(string str, int prefix)
{
	string *str_list;

	str = replace_string(str, "\r", "");
	str = replace_string(str, "\n\n", "$EOP");
	str = replace_string(str, "\n", "");
	str = replace_string(str, "$EOP$", "\n\n");

	str = sort_string(str, LINE_LEN, prefix);

	str_list = explode(str, "\n");
	str = implode(str_list, "\n" + PREFIX_STR);

	return str;
}

string input_file(string file)
{
	if (! previous_object() ||
	    geteuid(previous_object()) != "Kungfu")
		return 0;

	return read_file(file);
}

int help(object me)
{
	write(@HELP
ָ���ʽ��checkskill <��������> | <����������>

���ָ��������ָ����ĳ�ּ��ܻ��ܣ��������ƿ�������
�����������������ʦ�����߱���߱�����ܣ������ʾ��
�ü��ܵľ��м���Ϊ�ڹ������⹦�ܡ�ͬʱ���㻹���Բ鵽��
����ص�һЩ���ԣ����缼�ܵ����͡��Ƿ�˫�������ٶȡ���
������ʲô�ȵȣ�����������ڶ�������ص������Ļ����㻹
���Բ鵽����������ܵ�һЩ�ƹʡ�

���⣬������������һ���ɱ������ϲ��ļ��ܣ��������ʾ
��������Щ����������������

���ָ�skills

HELP);
	return 1;
}

