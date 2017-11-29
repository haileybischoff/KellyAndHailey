// tankHitSound sound made by wav2c
#include <stdint.h>

int32_t tankDeathSampleRate = 11127;
int32_t tankDeathSound_length = 6544;

int32_t tankDeathSound_data[] ={126,
124, 125, 124, 124, 125, 128, 130, 131, 130, 128, 126, 124, 124, 127, 129, 133, 134, 133, 128, 122, 
115, 109, 107, 111, 117, 127, 133, 136, 132, 127, 119, 113, 107, 108, 112, 117, 119, 121, 121, 127, 
130, 134, 140, 148, 155, 160, 161, 157, 148, 141, 131, 120, 108, 101, 98, 98, 97, 99, 106, 118, 
128, 130, 131, 133, 140, 148, 156, 157, 152, 141, 128, 123, 121, 120, 125, 133, 140, 139, 135, 134, 
138, 145, 154, 162, 168, 171, 171, 167, 161, 152, 135, 112, 88, 64, 50, 45, 43, 43, 46, 57, 
76, 92, 105, 116, 123, 130, 147, 163, 175, 182, 182, 180, 176, 176, 185, 203, 221, 230, 235, 241, 
240, 226, 211, 198, 182, 158, 128, 102, 87, 81, 73, 67, 68, 72, 69, 59, 43, 26, 20, 24, 
27, 30, 32, 41, 64, 95, 120, 139, 159, 178, 194, 206, 211, 210, 203, 192, 174, 142, 104, 61, 
24, 5, 0, 2, 20, 52, 79, 99, 121, 145, 167, 185, 197, 192, 178, 167, 162, 161, 161, 163, 
161, 145, 119, 91, 72, 60, 58, 65, 73, 88, 115, 140, 155, 167, 173, 168, 158, 154, 155, 157, 
167, 173, 170, 164, 155, 158, 175, 202, 229, 240, 239, 237, 234, 230, 218, 190, 150, 108, 67, 39, 
33, 50, 73, 91, 111, 133, 147, 148, 147, 137, 125, 116, 103, 85, 72, 69, 69, 66, 67, 82, 
107, 127, 132, 125, 111, 94, 86, 93, 103, 120, 138, 150, 164, 183, 201, 214, 208, 184, 148, 109, 
71, 51, 50, 55, 72, 101, 133, 162, 172, 160, 133, 104, 86, 78, 70, 62, 55, 50, 48, 53, 
76, 114, 161, 208, 234, 242, 245, 244, 242, 237, 228, 211, 182, 137, 89, 53, 23, 1, 0, 0, 
11, 41, 61, 69, 68, 71, 86, 100, 110, 116, 118, 121, 134, 159, 181, 210, 243, 254, 255, 254, 
243, 235, 236, 241, 246, 247, 238, 211, 175, 139, 99, 55, 16, 1, 0, 6, 42, 80, 97, 97, 
85, 67, 53, 54, 69, 81, 91, 99, 103, 108, 113, 120, 137, 170, 218, 255, 255, 253, 255, 246, 
222, 189, 158, 135, 130, 139, 154, 169, 179, 177, 153, 115, 65, 17, 0, 1, 0, 1, 0, 8, 
44, 90, 135, 176, 206, 223, 227, 223, 209, 190, 168, 144, 116, 76, 27, 0, 0, 1, 0, 2, 
33, 88, 129, 151, 160, 172, 193, 218, 240, 243, 228, 209, 203, 209, 223, 241, 252, 255, 248, 217, 
177, 150, 139, 145, 158, 173, 187, 190, 179, 165, 149, 134, 124, 117, 112, 110, 112, 115, 119, 117, 
103, 82, 62, 55, 67, 86, 103, 118, 129, 140, 159, 187, 209, 222, 239, 255, 255, 255, 254, 255, 
251, 210, 162, 123, 90, 81, 87, 97, 118, 145, 175, 195, 191, 166, 128, 87, 51, 34, 32, 33, 
35, 47, 72, 101, 118, 129, 142, 154, 164, 159, 133, 101, 77, 68, 66, 59, 59, 68, 74, 74, 
74, 82, 88, 85, 83, 79, 66, 53, 52, 59, 69, 92, 126, 162, 195, 212, 211, 199, 178, 164, 
160, 157, 148, 131, 114, 98, 91, 105, 136, 181, 219, 238, 248, 253, 255, 252, 236, 214, 192, 174, 
156, 137, 128, 132, 139, 144, 146, 147, 146, 144, 143, 144, 142, 142, 142, 143, 142, 142, 143, 142, 
143, 143, 143, 143, 141, 142, 141, 141, 141, 140, 139, 139, 138, 138, 137, 136, 135, 135, 133, 133, 
132, 131, 130, 129, 128, 128, 128, 128, 127, 127, 126, 127, 126, 125, 126, 125, 125, 124, 124, 123, 
124, 123, 122, 121, 122, 121, 121, 120, 119, 118, 118, 119, 118, 118, 117, 118, 117, 117, 117, 118, 
117, 118, 119, 119, 119, 120, 121, 121, 122, 121, 120, 113, 102, 98, 96, 91, 91, 106, 131, 151, 
157, 148, 133, 115, 98, 86, 80, 79, 83, 95, 123, 163, 212, 249, 255, 254, 254, 228, 180, 138, 
117, 112, 117, 114, 103, 90, 76, 65, 57, 51, 45, 34, 14, 1, 1, 0, 4, 22, 57, 107, 
165, 218, 249, 252, 238, 225, 219, 217, 209, 188, 163, 140, 119, 103, 90, 83, 73, 54, 45, 57, 
79, 97, 102, 99, 91, 82, 76, 75, 77, 85, 98, 112, 128, 148, 173, 219, 255, 255, 253, 255, 
253, 255, 249, 207, 161, 119, 81, 56, 29, 6, 0, 2, 24, 57, 78, 88, 92, 93, 92, 90, 
89, 90, 91, 92, 95, 99, 102, 106, 109, 113, 116, 119, 120, 122, 114, 92, 72, 58, 52, 56, 
67, 81, 102, 123, 142, 162, 178, 193, 204, 229, 254, 255, 254, 254, 255, 252, 255, 241, 169, 106, 
47, 3, 1, 0, 3, 34, 73, 98, 100, 90, 73, 55, 43, 34, 28, 28, 30, 33, 38, 44, 
45, 34, 25, 35, 61, 89, 105, 109, 106, 106, 122, 148, 178, 197, 197, 186, 171, 155, 141, 130, 
123, 118, 115, 114, 112, 106, 91, 74, 62, 63, 87, 124, 155, 170, 171, 163, 160, 164, 162, 156, 
144, 140, 148, 152, 152, 153, 166, 185, 195, 197, 198, 201, 198, 181, 155, 128, 104, 83, 68, 58, 
53, 51, 52, 54, 58, 59, 53, 55, 62, 69, 87, 111, 127, 132, 134, 132, 128, 127, 125, 123, 
121, 120, 119, 119, 118, 109, 106, 118, 130, 138, 141, 142, 141, 139, 137, 135, 133, 132, 131, 130, 
131, 130, 131, 132, 131, 132, 133, 132, 132, 130, 129, 131, 132, 133, 134, 133, 132, 131, 130, 128, 
125, 123, 120, 121, 130, 137, 141, 141, 139, 137, 134, 130, 128, 124, 120, 122, 124, 125, 126, 126, 
126, 125, 123, 124, 123, 122, 116, 102, 91, 94, 112, 132, 144, 157, 166, 165, 159, 149, 140, 133, 
127, 122, 119, 117, 115, 114, 114, 115, 114, 115, 116, 116, 117, 118, 119, 120, 121, 122, 123, 123, 
124, 125, 124, 125, 125, 124, 125, 121, 108, 90, 74, 70, 83, 101, 114, 123, 129, 131, 132, 133, 
137, 153, 175, 195, 218, 242, 255, 252, 230, 209, 190, 163, 135, 118, 108, 96, 84, 80, 91, 107, 
114, 119, 127, 133, 129, 116, 99, 82, 68, 58, 49, 37, 21, 19, 30, 40, 50, 66, 94, 129, 
165, 187, 190, 186, 174, 160, 147, 136, 128, 122, 119, 117, 117, 119, 121, 123, 124, 114, 99, 98, 
102, 105, 107, 111, 126, 154, 186, 204, 206, 195, 183, 178, 175, 168, 161, 164, 179, 192, 195, 197, 
202, 203, 193, 171, 149, 128, 108, 93, 83, 77, 74, 73, 74, 76, 79, 82, 87, 90, 93, 96, 
99, 97, 85, 71, 59, 52, 52, 58, 77, 108, 134, 154, 165, 174, 192, 217, 236, 242, 246, 249, 
241, 222, 203, 188, 168, 139, 107, 82, 63, 45, 28, 13, 11, 22, 37, 58, 81, 93, 97, 95, 
88, 88, 102, 128, 156, 168, 168, 167, 165, 159, 161, 169, 181, 189, 180, 157, 124, 91, 73, 64, 
61, 73, 95, 120, 135, 137, 130, 121, 110, 96, 85, 78, 69, 61, 53, 49, 52, 60, 85, 125, 
165, 195, 217, 229, 227, 228, 230, 225, 206, 180, 158, 142, 128, 125, 133, 145, 152, 145, 135, 125, 
113, 106, 100, 97, 96, 97, 98, 101, 103, 106, 109, 112, 115, 118, 121, 123, 125, 127, 128, 126, 
114, 95, 78, 65, 62, 66, 76, 91, 108, 127, 145, 163, 181, 210, 244, 255, 254, 255, 254, 255, 
237, 197, 167, 150, 134, 129, 135, 146, 155, 150, 136, 118, 91, 60, 25, 2, 1, 0, 3, 26, 
51, 74, 99, 118, 124, 124, 125, 128, 124, 112, 100, 88, 78, 71, 68, 65, 57, 53, 65, 87, 
109, 123, 129, 134, 137, 138, 138, 139, 140, 140, 141, 143, 145, 147, 149, 150, 151, 153, 153, 154, 
155, 155, 156, 155, 156, 155, 154, 155, 154, 152, 151, 150, 149, 147, 146, 145, 143, 139, 128, 109, 
91, 75, 67, 67, 73, 84, 99, 117, 143, 177, 200, 214, 231, 249, 255, 255, 250, 221, 186, 152, 
122, 107, 111, 129, 155, 180, 196, 201, 186, 150, 108, 72, 39, 9, 0, 1, 0, 1, 0, 4, 
37, 90, 139, 180, 199, 197, 190, 183, 170, 149, 128, 108, 92, 80, 74, 71, 71, 73, 69, 65, 
66, 63, 61, 61, 62, 75, 104, 145, 184, 205, 212, 207, 205, 214, 235, 252, 254, 255, 250, 230, 
200, 171, 155, 153, 153, 150, 152, 159, 169, 172, 163, 150, 134, 121, 111, 103, 100, 98, 99, 102, 
104, 108, 112, 114, 116, 118, 125, 131, 136, 138, 138, 136, 141, 146, 150, 153, 154, 153, 150, 148, 
146, 145, 144, 143, 143, 142, 142, 141, 141, 141, 140, 140, 141, 140, 141, 141, 140, 139, 140, 139, 
139, 138, 138, 137, 136, 135, 133, 133, 131, 129, 117, 101, 101, 111, 119, 120, 112, 104, 105, 113, 
118, 120, 119, 116, 119, 135, 165, 191, 206, 218, 230, 231, 214, 185, 149, 120, 106, 96, 94, 106, 
121, 127, 116, 105, 99, 90, 79, 64, 51, 42, 38, 39, 46, 56, 78, 117, 161, 205, 232, 238, 
240, 235, 228, 215, 188, 159, 139, 118, 91, 60, 35, 21, 11, 1, 3, 22, 52, 89, 117, 124, 
118, 103, 93, 99, 118, 132, 142, 154, 157, 160, 162, 158, 162, 174, 189, 200, 196, 176, 155, 145, 
147, 145, 141, 146, 155, 160, 160, 156, 151, 146, 140, 136, 135, 134, 134, 134, 136, 138, 139, 141, 
141, 143, 145, 147, 149, 150, 149, 150, 149, 148, 149, 148, 147, 147, 146, 144, 144, 143, 141, 138, 
135, 131, 122, 109, 105, 109, 113, 127, 149, 166, 173, 177, 173, 165, 160, 150, 143, 146, 157, 166, 
166, 156, 143, 129, 118, 107, 99, 94, 90, 87, 87, 85, 83, 88, 97, 102, 106, 108, 109, 110, 
111, 111, 112, 113, 112, 113, 115, 115, 116, 117, 117, 118, 119, 120, 120, 121, 123, 123, 124, 123, 
124, 126, 126, 126, 126, 126, 126, 127, 128, 128, 122, 116, 120, 127, 127, 118, 103, 87, 76, 79, 
101, 129, 148, 157, 161, 170, 184, 190, 183, 167, 144, 123, 105, 92, 86, 86, 96, 123, 161, 202, 
240, 255, 254, 246, 221, 186, 146, 112, 89, 70, 52, 45, 55, 74, 88, 98, 112, 126, 127, 123, 
117, 104, 96, 98, 107, 118, 122, 117, 108, 97, 88, 81, 77, 73, 68, 65, 58, 50, 44, 42, 
46, 56, 70, 97, 132, 165, 190, 205, 212, 215, 226, 247, 255, 254, 255, 255, 255, 254, 255, 244, 
209, 174, 134, 92, 59, 44, 52, 73, 100, 127, 146, 150, 138, 121, 106, 90, 73, 60, 48, 37, 
34, 30, 23, 16, 12, 23, 43, 60, 74, 87, 96, 110, 133, 157, 182, 207, 218, 218, 209, 194, 
178, 164, 153, 151, 165, 194, 228, 251, 255, 251, 233, 203, 164, 124, 86, 57, 37, 24, 28, 53, 
90, 131, 168, 196, 210, 201, 176, 151, 130, 115, 95, 67, 28, 3, 0, 0, 1, 0, 8, 49, 
102, 140, 157, 158, 160, 170, 184, 200, 213, 211, 196, 183, 171, 157, 132, 106, 91, 82, 73, 66, 
61, 60, 70, 97, 137, 185, 224, 240, 237, 227, 224, 225, 219, 201, 176, 150, 128, 109, 99, 99, 
114, 147, 188, 232, 254, 254, 255, 250, 234, 212, 178, 140, 99, 69, 56, 51, 58, 79, 107, 134, 
147, 147, 148, 150, 153, 156, 153, 136, 106, 75, 59, 58, 59, 60, 70, 86, 107, 121, 120, 106, 
94, 95, 104, 110, 105, 95, 88, 93, 116, 149, 184, 215, 228, 224, 214, 196, 176, 167, 165, 158, 
141, 124, 120, 128, 145, 167, 186, 197, 194, 177, 160, 147, 135, 126, 116, 110, 105, 102, 101, 101, 
103, 106, 108, 111, 102, 85, 78, 88, 101, 108, 109, 115, 132, 157, 183, 196, 190, 175, 165, 168, 
169, 162, 146, 128, 108, 93, 86, 94, 113, 130, 143, 160, 185, 214, 240, 251, 240, 212, 177, 140, 
114, 105, 102, 107, 124, 145, 168, 176, 171, 162, 155, 141, 116, 84, 51, 29, 27, 43, 70, 99, 
124, 139, 137, 123, 107, 84, 67, 64, 66, 63, 51, 37, 28, 33, 46, 64, 95, 129, 154, 171, 
182, 183, 183, 189, 199, 212, 222, 228, 228, 218, 199, 173, 148, 121, 85, 54, 42, 38, 37, 39, 
46, 70, 107, 151, 194, 219, 220, 213, 210, 214, 224, 228, 217, 193, 162, 131, 106, 87, 78, 82, 
104, 141, 183, 218, 231, 224, 210, 197, 179, 155, 131, 112, 97, 98, 117, 145, 176, 203, 222, 224, 
204, 168, 131, 106, 94, 93, 99, 106, 110, 111, 102, 77, 42, 9, 0, 1, 0, 0, 3, 16, 
34, 50, 66, 87, 119, 152, 176, 192, 200, 200, 204, 217, 228, 241, 253, 255, 254, 255, 252, 224, 
178, 136, 99, 74, 68, 85, 108, 122, 135, 151, 160, 153, 133, 107, 77, 54, 48, 54, 59, 65, 
79, 105, 131, 145, 155, 166, 178, 186, 191, 190, 184, 171, 157, 133, 97, 53, 13, 0, 1, 0, 
1, 29, 75, 104, 116, 115, 110, 116, 136, 157, 169, 169, 162, 159, 169, 190, 217, 245, 255, 253, 
255, 245, 220, 203, 191, 175, 152, 132, 113, 94, 87, 93, 107, 118, 119, 119, 125, 133, 143, 153, 
152, 139, 128, 112, 98, 97, 104, 108, 102, 91, 79, 70, 73, 91, 110, 126, 144, 168, 186, 204, 
220, 223, 215, 202, 186, 170, 159, 151, 147, 150, 167, 196, 232, 254, 254, 255, 248, 213, 164, 127, 
102, 80, 60, 52, 60, 75, 85, 91, 101, 109, 106, 89, 65, 42, 32, 40, 55, 65, 76, 93, 
105, 106, 105, 109, 111, 105, 98, 90, 75, 58, 52, 54, 55, 57, 70, 95, 127, 159, 177, 184, 
189, 193, 198, 194, 176, 148, 127, 113, 101, 102, 118, 138, 161, 182, 195, 196, 181, 165, 156, 150, 
146, 134, 113, 92, 85, 92, 100, 106, 116, 121, 117, 117, 123, 131, 143, 159, 168, 168, 165, 159, 
155, 165, 181, 196, 217, 242, 255, 254, 255, 254, 255, 250, 229, 203, 184, 165, 140, 120, 108, 99, 
85, 64, 47, 44, 52, 60, 61, 54, 45, 36, 38, 53, 72, 86, 103, 124, 141, 158, 180, 200, 
208, 207, 207, 205, 193, 176, 159, 135, 109, 81, 61, 59, 60, 62, 68, 85, 113, 143, 172, 192, 
193, 181, 165, 141, 122, 114, 113, 118, 125, 129, 128, 112, 83, 57, 40, 25, 14, 6, 3, 7, 
27, 55, 86, 120, 148, 171, 196, 220, 231, 231, 228, 215, 202, 189, 174, 165, 167, 173, 179, 173, 
161, 147, 128, 115, 103, 87, 70, 54, 44, 45, 64, 96, 126, 147, 166, 173, 166, 158, 155, 151, 
150, 160, 172, 174, 163, 144, 122, 101, 85, 78, 91, 118, 140, 153, 156, 157, 167, 175, 173, 169, 
162, 145, 124, 109, 102, 92, 83, 83, 96, 114, 123, 129, 132, 128, 127, 121, 114, 117, 124, 124, 
114, 97, 77, 59, 45, 39, 42, 58, 91, 129, 157, 170, 175, 184, 196, 201, 192, 175, 165, 164, 
170, 180, 188, 191, 183, 160, 125, 86, 49, 21, 14, 21, 34, 60, 94, 121, 137, 152, 167, 172, 
169, 163, 151, 140, 138, 140, 138, 127, 113, 107, 101, 93, 85, 79, 87, 109, 136, 155, 171, 181, 
179, 181, 176, 161, 144, 126, 110, 106, 118, 142, 173, 195, 201, 201, 191, 169, 145, 129, 118, 104, 
92, 81, 81, 98, 125, 154, 181, 199, 206, 194, 173, 154, 140, 129, 114, 87, 57, 24, 3, 0, 
3, 27, 69, 109, 143, 159, 162, 164, 166, 168, 171, 172, 169, 164, 158, 147, 135, 113, 80, 46, 
10, 0, 2, 0, 16, 39, 59, 83, 115, 156, 195, 217, 223, 218, 213, 219, 232, 240, 235, 222, 
213, 204, 189, 172, 166, 162, 154, 146, 146, 158, 176, 191, 192, 183, 170, 146, 118, 94, 80, 69, 
57, 53, 58, 62, 63, 70, 81, 89, 91, 98, 108, 115, 125, 133, 136, 145, 156, 169, 175, 165, 
141, 111, 78, 51, 41, 52, 77, 107, 125, 132, 134, 128, 120, 113, 100, 83, 67, 53, 48, 60, 
77, 99, 128, 161, 193, 213, 210, 192, 174, 166, 162, 154, 137, 122, 119, 126, 130, 131, 137, 147, 
148, 144, 142, 145, 153, 161, 163, 152, 128, 98, 68, 56, 65, 86, 115, 144, 161, 162, 159, 150, 
138, 136, 143, 155, 168, 174, 166, 155, 149, 142, 130, 111, 95, 94, 106, 125, 140, 142, 132, 117, 
107, 109, 113, 115, 117, 119, 122, 136, 164, 196, 217, 224, 223, 222, 216, 211, 207, 195, 178, 156, 
139, 135, 133, 128, 126, 132, 148, 159, 162, 162, 153, 141, 131, 117, 108, 108, 113, 121, 127, 129, 
124, 102, 68, 38, 15, 2, 0, 1, 0, 0, 1, 0, 11, 45, 83, 119, 153, 177, 186, 191, 
197, 199, 201, 210, 222, 233, 239, 238, 229, 201, 161, 116, 71, 33, 5, 0, 0, 11, 40, 72, 
111, 150, 177, 186, 180, 164, 154, 157, 169, 172, 165, 157, 152, 145, 134, 127, 130, 143, 154, 153, 
145, 140, 147, 160, 175, 187, 194, 191, 171, 147, 129, 114, 92, 64, 36, 12, 1, 0, 0, 7, 
26, 61, 109, 157, 193, 211, 213, 209, 212, 226, 243, 254, 251, 230, 199, 165, 132, 108, 97, 106, 
131, 162, 192, 211, 211, 200, 181, 153, 120, 87, 58, 40, 40, 53, 69, 96, 128, 160, 181, 185, 
181, 176, 173, 171, 167, 152, 125, 91, 64, 47, 29, 17, 20, 39, 71, 106, 137, 154, 154, 153, 
152, 144, 132, 123, 111, 102, 103, 114, 129, 139, 134, 118, 97, 77, 66, 73, 87, 100, 111, 122, 
138, 168, 199, 219, 232, 238, 229, 210, 197, 188, 177, 176, 184, 195, 202, 195, 182, 172, 162, 142, 
115, 90, 76, 78, 89, 104, 115, 110, 92, 66, 40, 29, 28, 28, 30, 32, 36, 44, 56, 69, 
84, 106, 138, 181, 215, 230, 230, 218, 207, 201, 193, 192, 198, 203, 196, 176, 155, 140, 123, 103, 
90, 91, 102, 108, 104, 91, 74, 59, 46, 43, 55, 74, 93, 117, 131, 135, 130, 126, 130, 146, 
169, 192, 207, 204, 188, 170, 141, 109, 76, 48, 39, 40, 41, 46, 61, 79, 90, 99, 115, 140, 
170, 195, 201, 190, 174, 160, 147, 139, 141, 151, 164, 167, 155, 134, 108, 83, 69, 76, 98, 129, 
157, 168, 164, 156, 151, 142, 129, 117, 110, 118, 137, 158, 167, 165, 166, 166, 161, 152, 150, 152, 
154, 161, 164, 166, 170, 165, 154, 138, 126, 125, 127, 126, 123, 118, 123, 133, 140, 141, 148, 164, 
184, 205, 220, 221, 203, 170, 139, 114, 88, 64, 51, 49, 48, 46, 52, 72, 99, 128, 154, 173, 
184, 186, 181, 170, 155, 138, 113, 77, 39, 10, 1, 0, 0, 1, 0, 9, 33, 57, 77, 93, 
110, 134, 162, 184, 196, 202, 203, 204, 218, 243, 254, 255, 254, 254, 255, 230, 192, 167, 153, 147, 
137, 130, 130, 133, 138, 131, 117, 101, 81, 56, 35, 29, 27, 32, 51, 73, 86, 87, 85, 92, 
109, 128, 149, 162, 159, 148, 141, 134, 121, 107, 102, 102, 96, 91, 93, 102, 117, 128, 139, 145, 
136, 122, 114, 111, 114, 122, 128, 133, 137, 138, 133, 117, 100, 93, 88, 81, 79, 78, 77, 86, 
105, 120, 126, 124, 119, 119, 133, 157, 177, 185, 184, 178, 180, 185, 187, 186, 181, 182, 195, 216, 
240, 254, 249, 228, 198, 166, 135, 111, 96, 87, 87, 103, 129, 164, 193, 203, 202, 193, 169, 138, 
115, 98, 83, 78, 84, 95, 106, 103, 95, 85, 65, 40, 15, 1, 0, 0, 4, 22, 49, 72, 
92, 110, 118, 117, 109, 99, 92, 97, 110, 124, 142, 155, 164, 173, 174, 173, 171, 160, 142, 124, 
106, 92, 83, 81, 90, 114, 149, 187, 220, 238, 235, 212, 184, 160, 137, 122, 119, 121, 118, 106, 
95, 91, 87, 79, 78, 89, 111, 137, 157, 162, 152, 141, 134, 125, 113, 100, 96, 107, 129, 151, 
167, 182, 199, 214, 220, 211, 198, 189, 183, 180, 177, 174, 164, 143, 121, 100, 74, 48, 28, 13, 
11, 29, 64, 101, 127, 140, 145, 145, 145, 157, 171, 179, 183, 181, 178, 175, 173, 173, 182, 206, 
235, 253, 255, 254, 255, 247, 216, 175, 134, 95, 69, 64, 73, 91, 110, 126, 132, 121, 96, 63, 
30, 13, 15, 26, 32, 33, 37, 50, 71, 85, 95, 109, 124, 138, 151, 154, 143, 129, 119, 109, 
95, 73, 57, 55, 68, 88, 112, 132, 149, 159, 163, 158, 140, 121, 108, 103, 105, 111, 117, 123, 
127, 128, 122, 102, 76, 59, 56, 69, 89, 103, 105, 103, 107, 122, 137, 143, 142, 137, 135, 145, 
166, 184, 192, 189, 179, 168, 158, 150, 146, 146, 150, 156, 174, 203, 231, 245, 243, 235, 226, 211, 
190, 164, 139, 117, 99, 93, 104, 126, 150, 173, 187, 190, 176, 142, 105, 75, 57, 43, 30, 23, 
14, 2, 0, 1, 0, 0, 7, 27, 49, 61, 69, 82, 95, 107, 124, 146, 167, 185, 194, 186, 
162, 136, 117, 99, 82, 71, 73, 78, 80, 82, 87, 101, 119, 131, 141, 157, 171, 182, 195, 201, 
197, 187, 175, 175, 185, 202, 221, 236, 236, 218, 188, 152, 119, 95, 91, 102, 124, 145, 152, 156, 
160, 161, 151, 131, 116, 110, 114, 125, 131, 128, 113, 94, 76, 62, 56, 66, 85, 104, 118, 128, 
141, 164, 191, 211, 221, 230, 240, 245, 246, 239, 217, 183, 143, 105, 72, 47, 39, 49, 64, 84, 
114, 145, 174, 196, 204, 193, 168, 144, 129, 126, 128, 127, 119, 112, 100, 82, 65, 51, 52, 68, 
95, 123, 137, 139, 133, 132, 139, 142, 142, 142, 137, 133, 136, 144, 155, 166, 173, 174, 162, 135, 
109, 91, 85, 90, 101, 114, 126, 133, 137, 137, 125, 106, 90, 71, 59, 60, 67, 71, 77, 83, 
83, 79, 74, 71, 74, 90, 111, 128, 140, 149, 156, 164, 184, 210, 228, 237, 242, 237, 226, 217, 
198, 174, 149, 129, 123, 119, 120, 125, 126, 128, 129, 128, 128, 122, 110, 98, 96, 104, 117, 130, 
139, 134, 116, 89, 60, 34, 22, 28, 47, 62, 78, 92, 97, 94, 91, 97, 111, 118, 117, 108, 
98, 96, 106, 126, 147, 166, 182, 187, 175, 159, 147, 134, 119, 104, 99, 97, 90, 87, 85, 78, 
69, 60, 59, 72, 96, 120, 133, 137, 137, 142, 151, 157, 160, 159, 161, 174, 194, 209, 218, 223, 
218, 205, 186, 168, 159, 162, 171, 174, 176, 182, 183, 177, 168, 162, 156, 142, 121, 98, 78, 71, 
71, 69, 73, 85, 105, 124, 132, 130, 124, 113, 107, 111, 118, 128, 141, 149, 148, 143, 137, 137, 
141, 141, 139, 144, 157, 175, 188, 187, 180, 170, 150, 126, 101, 78, 60, 50, 47, 54, 75, 106, 
140, 167, 179, 182, 176, 164, 156, 151, 145, 131, 112, 91, 71, 56, 50, 57, 79, 110, 141, 169, 
184, 182, 177, 171, 160, 144, 131, 126, 125, 127, 129, 130, 125, 108, 85, 59, 35, 24, 27, 39, 
54, 68, 82, 101, 129, 161, 184, 200, 211, 212, 212, 216, 216, 207, 199, 195, 188, 173, 153, 135, 
129, 129, 129, 128, 130, 138, 147, 154, 159, 160, 157, 145, 126, 109, 97, 86, 73, 65, 57, 48, 
39, 32, 31, 40, 63, 95, 123, 139, 145, 147, 152, 166, 182, 189, 194, 196, 189, 184, 176, 161, 
144, 128, 121, 121, 123, 129, 135, 134, 129, 122, 119, 123, 125, 123, 119, 118, 127, 143, 162, 175, 
174, 168, 156, 136, 115, 101, 98, 103, 112, 121, 128, 126, 113, 98, 81, 59, 38, 18, 5, 4, 
16, 33, 55, 81, 101, 121, 135, 141, 141, 146, 150, 153, 159, 162, 164, 171, 180, 191, 191, 184, 
174, 158, 143, 131, 119, 104, 90, 78, 70, 67, 75, 94, 112, 132, 153, 167, 180, 195, 202, 201, 
197, 196, 195, 191, 177, 154, 127, 101, 79, 63, 58, 70, 93, 113, 128, 142, 149, 145, 140, 139, 
137, 130, 125, 117, 111, 113, 128, 149, 173, 195, 210, 215, 205, 187, 171, 156, 137, 119, 108, 101, 
94, 86, 85, 87, 87, 79, 72, 71, 81, 98, 113, 120, 116, 111, 111, 109, 112, 119, 123, 131, 
146, 156, 158, 152, 140, 133, 133, 135, 140, 150, 153, 151, 154, 162, 173, 177, 172, 166, 164, 166, 
167, 158, 145, 128, 114, 101, 94, 99, 109, 121, 134, 144, 151, 159, 157, 149, 143, 142, 147, 146, 
138, 125, 109, 94, 82, 78, 86, 103, 126, 144, 152, 153, 154, 151, 142, 129, 124, 117, 106, 96, 
87, 75, 61, 48, 42, 46, 55, 69, 85, 95, 101, 110, 124, 142, 161, 170, 169, 168, 169, 168, 
164, 151, 131, 109, 87, 70, 61, 57, 64, 82, 101, 124, 149, 173, 188, 195, 196, 189, 175, 163, 
155, 148, 145, 150, 159, 168, 167, 161, 152, 137, 120, 106, 103, 109, 119, 126, 127, 127, 129, 127, 
119, 105, 89, 74, 68, 72, 81, 90, 100, 114, 127, 134, 140, 149, 157, 163, 170, 171, 173, 179, 
183, 180, 169, 154, 145, 134, 124, 112, 103, 103, 107, 109, 112, 120, 133, 149, 166, 178, 179, 168, 
148, 131, 123, 117, 109, 104, 100, 91, 81, 71, 68, 76, 93, 114, 134, 148, 150, 148, 145, 144, 
142, 135, 125, 118, 116, 116, 114, 106, 92, 76, 62, 54, 52, 54, 63, 76, 90, 106, 126, 148, 
170, 185, 193, 196, 204, 216, 226, 225, 216, 206, 197, 183, 168, 156, 153, 155, 153, 149, 148, 147, 
140, 131, 126, 122, 113, 99, 81, 66, 60, 60, 63, 72, 81, 90, 100, 105, 104, 106, 114, 127, 
140, 148, 149, 148, 148, 149, 147, 138, 128, 119, 107, 100, 93, 86, 78, 71, 69, 70, 76, 91, 
110, 124, 134, 143, 153, 170, 186, 195, 195, 191, 190, 192, 189, 179, 166, 156, 147, 136, 127, 125, 
129, 139, 150, 160, 166, 163, 151, 137, 128, 118, 102, 85, 68, 57, 56, 59, 68, 81, 92, 104, 
115, 119, 122, 127, 131, 135, 142, 146, 150, 157, 165, 166, 160, 150, 143, 138, 134, 137, 142, 143, 
139, 128, 118, 106, 96, 90, 90, 99, 112, 126, 141, 152, 156, 154, 149, 148, 153, 163, 173, 175, 
168, 152, 133, 115, 99, 90, 92, 104, 121, 136, 144, 146, 146, 145, 138, 124, 110, 103, 103, 108, 
111, 109, 107, 104, 95, 83, 74, 71, 79, 93, 104, 111, 114, 121, 133, 145, 157, 168, 175, 177, 
175, 170, 163, 149, 131, 116, 100, 83, 67, 57, 52, 55, 71, 95, 123, 145, 157, 160, 161, 165, 
172, 180, 182, 174, 162, 154, 146, 140, 141, 148, 156, 162, 160, 157, 155, 156, 157, 156, 155, 150, 
137, 126, 118, 113, 112, 107, 100, 98, 100, 98, 96, 96, 95, 95, 98, 98, 98, 102, 109, 116, 
126, 134, 141, 152, 162, 168, 169, 169, 172, 176, 177, 176, 173, 169, 158, 141, 127, 110, 92, 78, 
72, 77, 89, 104, 117, 124, 125, 123, 117, 112, 113, 116, 116, 116, 116, 113, 113, 115, 112, 107, 
103, 104, 114, 128, 136, 140, 138, 133, 129, 129, 137, 148, 155, 156, 154, 155, 158, 159, 154, 145, 
138, 132, 125, 116, 109, 102, 96, 96, 102, 115, 132, 149, 158, 157, 147, 134, 121, 111, 109, 109, 
112, 121, 129, 133, 130, 125, 121, 117, 111, 106, 106, 107, 110, 115, 118, 122, 124, 125, 127, 126, 
121, 115, 109, 103, 104, 114, 128, 145, 155, 158, 158, 154, 147, 141, 132, 123, 112, 103, 98, 95, 
95, 101, 115, 132, 154, 175, 189, 192, 187, 182, 175, 164, 151, 142, 137, 135, 132, 125, 117, 109, 
100, 89, 81, 81, 89, 103, 115, 120, 121, 120, 119, 124, 131, 140, 150, 159, 162, 162, 165, 171, 
180, 188, 193, 195, 190, 177, 164, 152, 141, 127, 111, 99, 94, 89, 90, 98, 106, 111, 110, 110, 
114, 123, 132, 137, 136, 129, 125, 122, 119, 120, 121, 122, 125, 125, 123, 119, 114, 112, 116, 127, 
140, 154, 162, 159, 152, 147, 139, 131, 123, 115, 113, 118, 127, 138, 144, 143, 141, 134, 124, 112, 
101, 93, 92, 96, 102, 111, 123, 132, 135, 132, 129, 128, 125, 124, 122, 119, 114, 107, 102, 98, 
98, 105, 118, 133, 146, 152, 155, 155, 154, 153, 147, 138, 130, 125, 117, 108, 103, 101, 99, 95, 
88, 85, 85, 87, 92, 96, 100, 101, 102, 103, 108, 117, 126, 135, 145, 149, 151, 149, 146, 144, 
148, 156, 166, 174, 175, 173, 171, 167, 159, 147, 136, 128, 122, 118, 120, 123, 124, 120, 116, 115, 
114, 112, 109, 106, 105, 109, 119, 131, 140, 143, 144, 146, 146, 146, 149, 153, 152, 150, 149, 148, 
145, 140, 136, 134, 129, 122, 113, 110, 112, 118, 126, 131, 136, 139, 137, 131, 124, 119, 115, 109, 
105, 102, 98, 94, 94, 97, 101, 105, 112, 121, 128, 137, 145, 148, 149, 152, 155, 154, 151, 148, 
144, 141, 139, 140, 144, 155, 167, 173, 177, 181, 183, 183, 177, 164, 148, 130, 115, 104, 102, 107, 
115, 125, 132, 137, 136, 128, 116, 107, 102, 100, 97, 92, 86, 84, 86, 91, 97, 107, 120, 131, 
140, 146, 145, 141, 138, 136, 135, 130, 125, 121, 120, 121, 120, 116, 114, 110, 106, 105, 105, 103, 
103, 108, 113, 118, 128, 138, 144, 147, 149, 147, 141, 140, 139, 138, 140, 145, 150, 149, 144, 137, 
131, 126, 122, 119, 120, 127, 133, 137, 141, 147, 150, 149, 148, 149, 148, 146, 140, 133, 128, 125, 
122, 126, 133, 143, 151, 157, 160, 159, 153, 142, 128, 113, 101, 91, 83, 75, 71, 75, 80, 86, 
97, 109, 121, 130, 137, 137, 133, 131, 130, 129, 129, 128, 128, 122, 115, 110, 102, 94, 88, 84, 
83, 85, 90, 96, 105, 114, 123, 132, 146, 156, 163, 168, 169, 168, 169, 173, 179, 182, 182, 181, 
180, 174, 164, 152, 144, 136, 127, 120, 118, 120, 125, 130, 134, 137, 135, 128, 118, 109, 105, 103, 
101, 96, 91, 88, 85, 85, 87, 92, 102, 116, 130, 139, 142, 142, 141, 144, 149, 157, 163, 166, 
162, 156, 148, 137, 126, 115, 107, 105, 105, 109, 113, 118, 119, 117, 118, 123, 126, 128, 128, 128, 
128, 130, 136, 144, 151, 154, 157, 159, 156, 151, 148, 145, 143, 139, 131, 126, 118, 111, 107, 102, 
100, 100, 101, 104, 110, 115, 115, 114, 111, 110, 112, 114, 116, 117, 118, 120, 122, 124, 128, 133, 
140, 147, 153, 156, 159, 160, 160, 158, 152, 145, 140, 135, 132, 130, 131, 133, 132, 131, 128, 123, 
118, 113, 111, 113, 117, 122, 125, 125, 124, 123, 118, 114, 111, 111, 115, 120, 123, 124, 122, 118, 
117, 118, 119, 121, 126, 128, 128, 129, 132, 133, 133, 132, 132, 135, 137, 138, 137, 136, 135, 133, 
134, 139, 144, 149, 151, 153, 151, 146, 140, 133, 128, 123, 120, 123, 128, 131, 134, 137, 140, 139, 
135, 130, 126, 124, 125, 127, 128, 128, 123, 116, 109, 101, 95, 93, 96, 101, 106, 111, 117, 123, 
128, 133, 140, 146, 151, 154, 152, 147, 143, 140, 134, 127, 121, 116, 114, 112, 109, 108, 109, 114, 
119, 121, 126, 130, 134, 139, 142, 142, 140, 139, 135, 134, 136, 141, 148, 152, 152, 151, 147, 142, 
135, 131, 130, 129, 128, 127, 124, 125, 127, 127, 127, 128, 128, 128, 127, 126, 124, 123, 122, 121, 
119, 117, 117, 119, 123, 127, 128, 130, 133, 135, 138, 139, 138, 138, 137, 133, 129, 126, 122, 118, 
116, 114, 113, 114, 114, 115, 117, 119, 123, 128, 132, 134, 134, 132, 133, 135, 137, 138, 138, 137, 
137, 136, 134, 132, 133, 133, 132, 131, 130, 128, 128, 129, 130, 131, 131, 128, 126, 124, 124, 123, 
122, 120, 116, 116, 115, 115, 117, 119, 120, 121, 121, 122, 124, 128, 131, 133, 134, 136, 140, 145, 
147, 147, 146, 145, 143, 141, 140, 141, 140, 136, 131, 129, 127, 123, 119, 117, 115, 116, 118, 121, 
123, 123, 122, 121, 120, 123, 127, 131, 133, 132, 128, 124, 119, 115, 115, 119, 124, 128, 131, 131, 
128, 126, 122, 119, 115, 113, 113, 114, 116, 118, 121, 124, 126, 127, 128, 129, 128, 128, 128, 128, 
129, 131, 135, 139, 142, 144, 144, 142, 138, 133, 128, 125, 122, 118, 115, 113, 111, 111, 112, 116, 
123, 128, 133, 138, 140, 141, 142, 143, 144, 146, 147, 149, 146, 142, 137, 132, 128, 127, 127, 130, 
135, 140, 142, 143, 142, 141, 138, 133, 128, 123, 118, 116, 117, 118, 120, 126, 130, 133, 135, 135, 
134, 135, 134, 134, 133, 132, 131, 129, 126, 122, 117, 110, 104, 101, 101, 104, 109, 114, 117, 119, 
120, 121, 124, 128, 130, 132, 133, 133, 134, 137, 139, 141, 145, 148, 152, 152, 149, 144, 140, 135, 
131, 128, 125, 125, 127, 128, 130, 132, 132, 130, 126, 121, 118, 116, 114, 113, 114, 113, 112, 113, 
116, 120, 125, 129, 133, 134, 133, 133, 132, 132, 132, 131, 130, 128, 126, 124, 120, 118, 117, 116, 
117, 118, 119, 119, 120, 122, 125, 128, 132, 134, 135, 136, 135, 136, 135, 136, 138, 139, 140, 139, 
138, 135, 131, 128, 126, 122, 119, 119, 120, 124, 127, 127, 128, 129, 130, 129, 129, 128, 128, 128, 
128, 129, 129, 129, 130, 132, 133, 132, 131, 130, 130, 131, 132, 133, 133, 132, 131, 129, 127, 125, 
121, 119, 119, 120, 123, 125, 127, 128, 128, 127, 126, 126, 127, 128, 128, 128, 128, 129, 130, 131, 
134, 136, 137, 138, 139, 138, 137, 135, 134, 131, 128, 125, 123, 120, 120, 121, 122, 126, 128, 129, 
130, 131, 132, 131, 130, 130, 129, 128, 128, 128, 128, 127, 125, 123, 121, 120, 119, 120, 121, 123, 
124, 126, 127, 128, 130, 132, 133, 133, 134, 135, 134, 135, 136, 135, 135, 136, 137, 137, 136, 133, 
130, 128, 128, 127, 128, 128, 128, 129, 130, 131, 132, 131, 129, 128, 126, 124, 123, 123, 123, 122, 
121, 121, 122, 125, 128, 130, 132, 132, 130, 128, 127, 127, 128, 128, 128, 129, 131, 132, 131, 128, 
126, 123, 119, 117, 116, 115, 116, 118, 120, 124, 129, 134, 138, 140, 139, 136, 133, 132, 131, 131, 
132, 131, 131, 131, 130, 128, 126, 125, 123, 122, 121, 122, 123, 124, 126, 127, 128, 129, 129, 130, 
131, 131, 130, 129, 128, 126, 126, 127, 128, 128, 129, 130, 130, 129, 129, 128, 127, 127, 126, 127, 
128, 130, 132, 133, 135, 137, 139, 139, 138, 136, 136, 135, 134, 132, 130, 128, 128, 126, 125, 126, 
127, 128, 128, 127, 126, 126, 126, 127, 126, 127, 127, 126, 127, 126, 127, 128, 128, 128, 128, 128, 
128, 128, 128, 128, 128, 129, 128, 128, 128, 127, 126, 127, 127, 128, 128, 129, 130, 129, 130, 129, 
130, 129, 129, 130, 129, 129, 128, 127, 127, 127, 126, 126, 126, 127, 128, 127, 128, 128, 127, 127, 
126, 126, 127, 126, 127, 126, 126, 127, 126, 126, 126, 125, 125, 126, 127, 126, 127, 128, 127, 127, 
127, 127, 128, 129, 129, 129, 128, 128, 129, 128, 128, 128, 129, 128, 129, 128, 128, 128, 127, 127, 
126, 127, 128, 128, 129, 129, 128, 128, 127, 126, 127, 128, 128, 129, 128, 128, 128, 128, 127, 128, 
128, 128, 130, 131, 132, 132, 131, 130, 128, 128, 128, 129, 131, 131, 130, 131, 130, 129, 128, 128, 
129, 128, 129, 128, 128, 126, 125, 125, 124, 125, 128, 128, 129, 130, 129, 128, 128, 126, 125, 126, 
128, 129, 130, 129, 128, 128, 126, 124, 124, 125, 128, 128, 129, 128, 128, 129, 128, 128, 128, 129, 
131, 132, 132, 131, 130, 129, 128, 128, 129, 131, 132, 134, 134, 133, 131, 129, 127, 126, 126, 127, 
128, 129, 130, 130, 129, 130, 129, 128, 128, 129, 130, 131, 130, 129, 128, 126, 125, 124, 124, 125, 
128, 128, 128, 129, 129, 129, 130, 130, 131, 132, 131, 132, 131, 129, 129, 128, 126, 126, 125, 125, 
126, 125, 126, 126, 127, 128, 128, 129, 130, 130, 131, 132, 132, 131, 130, 129, 129, 128, 128, 129, 
131, 132, 132, 133, 133, 132, 132, 131, 131, 130, 128, 128, 128, 128, 127, 126, 125, 125, 123, 122, 
121, 120, 121, 122, 125, 126, 128, 128, 128, 129, 130, 131, 132, 132, 131, 130, 130, 128, 128, 128, 
127, 128, 126, 125, 126, 125, 126, 128, 128, 128, 129, 130, 129, 130, 129, 128, 128, 127, 126, 126, 
125, 124, 125, 124, 124, 124, 123, 123, 124, 127, 128, 128, 129, 129, 130, 131, 132, 133, 133, 134, 
135, 134, 135, 134, 135, 134, 132, 131, 130, 128, 128, 128, 126, 127, 126, 127, 128, 128, 128, 128, 
127, 127, 128, 127, 126, 125, 124, 123, 122, 122, 123, 124, 125, 128, 128, 129, 130, 130, 129, 130, 
128, 128, 128, 128, 127, 126, 126, 126, 125, 123, 122, 122, 122, 123, 125, 126, 126, 128, 128, 128, 
130, 131, 132, 131, 131, 132, 131, 132, 131, 132, 131, 130, 129, 127, 126, 125, 125, 126, 128, 128, 
128, 129, 130, 130, 129, 128, 128, 129, 128, 128, 129, 129, 128, 129, 130, 129, 129, 129, 128, 128, 
128, 129, 130, 129, 129, 130, 131, 131, 129, 128, 128, 128, 128, 128, 129, 130, 131, 130, 131, 130, 
129, 129, 128, 128, 128, 128, 128, 128, 128, 128, 130, 131, 131, 132, 132, 130, 129, 128, 128, 127, 
126, 125, 125, 126, 125, 126, 127, 128, 128, 128, 128, 127, 126, 127, 126, 126, 127, 128, 128, 128, 
128, 128, 128, 128, 128, 127, 127, 126, 125, 125, 126, 127, 127, 127, 128, 128, 129, 129, 130, 131, 
130, 130, 131, 130, 130, 131, 129, 128, 128, 127, 126, 126, 125, 126, 127, 127, 127, 128, 128, 128, 
128, 128, 128, 129, 128, 129, 130, 130, 131, 132, 131, 131, 132, 131, 131, 132, 131, 131, 132, 132, 
131, 130, 129, 128, 127, 126, 127, 126, 126, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 127, 
127, 126, 127, 126, 127, 128, 128, 128, 128, 128, 127, 126, 127, 127, 127, 128, 128, 128, 128, 128, 
128, 127, 126, 125, 125, 126, 125, 125, 126, 126, 128, 128, 129, 130, 131, 132, 131, 131, 132, 131, 
130, 130, 129, 128, 128, 128, 128, 128, 128, 128, 128, 128, 129, 128, 128, 129, 129, 128, 128, 127, 
126, 126, 127, 128, 128, 128, 128, 128, 128, 127, 127, 128, 128, 128, 128, 128, 128, 128, 128, 128, 
129, 128, 129, 128, 129, 130, 129, 128, 128, 128, 128, 127, 126, 127, 126, 127, 128, 128, 129, 130, 
129, 130, 131, 130, 131, 130, 129, 129, 128, 128, 128, 128, 127, 128, 127, 128, 128, 128, 128, 128, 
129, 128, 128, };
